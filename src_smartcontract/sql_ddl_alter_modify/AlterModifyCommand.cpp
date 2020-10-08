/*
 * AlterModifyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

#include "sql_ddl/DdlColumnDescriptor.h"
#include "sql_ddl/ColumnTypeDescriptor.h"

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"

#include "sql_join_parts/TableIdentifier.h"

#include "schema/SchemaManager.h"

#include "schema_alter_ctx/ColumnModifyContext.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "sql_ddl_alter/IndexChecker.h"

#include "engine/CdbException.h"

#include "table_record_value/AbstractCdbValue.h"

#include "base_io/ByteBuffer.h"

#include "vm/VirtualMachine.h"

namespace alinous {

AlterModifyCommand::AlterModifyCommand(const AlterModifyCommand& inst) : AbstractAlterDdlWithTypeDesc(CodeElement::DDL_ALTER_MODIFY) {
	this->columnDescriptor = copyColumnDescriptor(inst.columnDescriptor);
	this->longValue = inst.longValue;
}


AlterModifyCommand::AlterModifyCommand() : AbstractAlterDdlWithTypeDesc(CodeElement::DDL_ALTER_MODIFY) {

}

AlterModifyCommand::~AlterModifyCommand() {

}

int AlterModifyCommand::binarySize() const {
	checkNotNull(this->columnDescriptor);

	int total = sizeof(uint16_t);

	total += this->columnDescriptor->binarySize();

	return total;
}

void AlterModifyCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->columnDescriptor);

	out->putShort(CodeElement::DDL_ALTER_MODIFY);
	this->columnDescriptor->toBinary(out);
}

void AlterModifyCommand::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::DDL_COLMUN_DESC);

	this->columnDescriptor = dynamic_cast<DdlColumnDescriptor*>(element);
}

AbstractAlterCommandLog* AlterModifyCommand::getCommandLog() {
	AlterModifyCommandLog* log = new AlterModifyCommandLog();

	log->setLength(this->longValue);
	log->setCommand(new AlterModifyCommand(*this));

	return log;
}

void AlterModifyCommand::preAnalyze(AnalyzeContext* actx) {
	ColumnTypeDescriptor* typeDesc = this->columnDescriptor->getTypeDesc();
	AbstractSQLExpression* length = typeDesc->getLengthExp();

	if(length != nullptr){
		length->setParent(this);
		length->preAnalyze(actx);
	}

	AbstractSQLExpression* defaultValue = this->columnDescriptor->getDefaultValue();
	if(defaultValue != nullptr){
		defaultValue->setParent(this);
		defaultValue->preAnalyze(actx);
	}
}

void AlterModifyCommand::analyzeTypeRef(AnalyzeContext* actx) {
	ColumnTypeDescriptor* typeDesc = this->columnDescriptor->getTypeDesc();
	AbstractSQLExpression* length = typeDesc->getLengthExp();

	if(length != nullptr){
		length->analyzeTypeRef(actx);
	}

	AbstractSQLExpression* defaultValue = this->columnDescriptor->getDefaultValue();
	if(defaultValue != nullptr){
		defaultValue->analyzeTypeRef(actx);
	}
}

void AlterModifyCommand::analyze(AnalyzeContext* actx) {
	analyzeLengthOfValiable(actx);

	AbstractSQLExpression* defaultValue = this->columnDescriptor->getDefaultValue();
	if(defaultValue != nullptr){
		defaultValue->analyze(actx);
	}
}

void AlterModifyCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterModifyCommandLog* modifyLog = dynamic_cast<AlterModifyCommandLog*>(log);
	AlterModifyCommand* command = modifyLog->getCommand();

	UnicodeString* str = interpretDefaultString(vm);
	command->setDefaultValueStr(str);


	validate(vm, modifyLog, tableId);
}

void AlterModifyCommand::validate(VirtualMachine* vm, AlterModifyCommandLog* log, TableIdentifier* tableId) {
	CodableDatabase* db = vm->getDb();
	SchemaManager* scmagr = db->getSchemaManager();
	CdbStorageManager* storagemgr = db->getStorageManager();

	const UnicodeString* scName = tableId->getSchema();
	const UnicodeString* tblName = tableId->getTableName();
	CdbTable* table = scmagr->getTable(scName, tblName);

	const UnicodeString* name = this->columnDescriptor->getName();
	CdbTableColumn* column = table->getColumn(name);


	AlterModifyCommand* command = log->getCommand();
	const UnicodeString* defstr = command->getDefaultValueStr();

	ColumnModifyContext* modifyContext = column->createModifyContextwithChange(this, defstr, false); __STP(modifyContext);
	modifyContext->setColumn(column);
	modifyContext->analyze();

	ColumnModifyContext::UniqueChage uchange = modifyContext->getUniqueChange();

	if(uchange == ColumnModifyContext::UniqueChage::TO_UNIQUE || (modifyContext->isUnique() && modifyContext->isTypeChanged())){
		bool currentUnique = column->isUnique();
		uint8_t currentType = column->getType();
		uint8_t nextType = modifyContext->getCdbType();
		ColumnModifyContext::LengthChange lengthChange = modifyContext->getLengthChange();

		uint8_t strType = AbstractCdbValue::TYPE_STRING;

		if((currentType == nextType && nextType == strType) && currentUnique
				&& lengthChange != ColumnModifyContext::LengthChange::LENGTH_CHANGE_SHORTER){
			return;
		}

		IndexChecker checker(db, modifyContext);

		bool result = checker.checkUnique(table, column);
		if(!result){
			throw new CdbException(L"Can not set the column unique because of table data.", __FILE__, __LINE__);
		}
	}

	/**
	 * When the type changed, need to check other indexes containing the column
	 */
	if(modifyContext->isTypeChanged()){
		// FIXME check multiple index unique
	}
}

} /* namespace alinous */
