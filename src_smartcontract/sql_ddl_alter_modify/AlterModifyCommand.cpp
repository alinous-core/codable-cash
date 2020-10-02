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

#include "sql/AbstractSQLExpression.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sql_expression/SQLLiteral.h"

#include "instance/AbstractVmInstance.h"
#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance_gc/StackFloatingVariableHandler.h"

#include "instance_ref/PrimitiveReference.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "instance_string/VmStringInstance.h"

#include "instance_exception/TypeCastExceptionClassDeclare.h"
#include "instance_exception/ExceptionInterrupt.h"

#include "engine/CodableDatabase.h"

#include "sql_join_parts/TableIdentifier.h"

#include "schema/SchemaManager.h"
#include "schema/ColumnModifyContext.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "sql_ddl_alter/IndexChecker.h"

#include "engine/CdbException.h"

namespace alinous {

AlterModifyCommand::AlterModifyCommand(const AlterModifyCommand& inst) : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_MODIFY) {
	this->columnDescriptor = copyColumnDescriptor(inst.columnDescriptor);
	this->longValue = inst.longValue;
}


AlterModifyCommand::AlterModifyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_MODIFY) {
	this->columnDescriptor = nullptr;
	this->longValue = 0;
}

AlterModifyCommand::~AlterModifyCommand() {
	delete this->columnDescriptor;
}

void AlterModifyCommand::setColumnDescriptor(DdlColumnDescriptor* columnDescriptor) noexcept {
	delete this->columnDescriptor;
	this->columnDescriptor = columnDescriptor;
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
	ColumnTypeDescriptor* typeDesc = this->columnDescriptor->getTypeDesc();

	AbstractSQLExpression* length = typeDesc->getLengthExp();

	if(length != nullptr){
		bool error = false;
		short kind = length->getKind();
		if(kind != CodeElement::SQL_EXP_LITERAL){
			const UnicodeString* tname = typeDesc->getTypeName();
			actx->addValidationError(ValidationError::DB_LENGTH_IS_NOT_INTEGER, this, L"The type {0}'s length must be integer value.", {tname});

			error = true;
		}

		if(!error){
			SQLLiteral* lit = dynamic_cast<SQLLiteral*>(length);
			uint8_t litType = lit->getLiteralType();
			if(litType != SQLLiteral::TYPE_NUMBER){
				const UnicodeString* tname = typeDesc->getTypeName();
				actx->addValidationError(ValidationError::DB_LENGTH_IS_NOT_INTEGER, this, L"The type {0}'s length must be integer value.", {tname});
			}

			lit->analyze(actx);

			this->longValue = lit->getLongv();
			if(this->longValue < 1){
				const UnicodeString* tname = typeDesc->getTypeName();
				actx->addValidationError(ValidationError::DB_LENGTH_IS_NOT_CORRECT_INTEGER, this, L"The type {0}'s length must be greater than 0.", {tname});
			}
		}
	}

	AbstractSQLExpression* defaultValue = this->columnDescriptor->getDefaultValue();
	if(defaultValue != nullptr){
		defaultValue->analyze(actx);
	}
}

void AlterModifyCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterModifyCommandLog* modifyLog = dynamic_cast<AlterModifyCommandLog*>(log);

	AbstractSQLExpression* defaultValue = this->columnDescriptor->getDefaultValue();
	if(defaultValue != nullptr){
		StackFloatingVariableHandler releaser(vm->getGc());

		AbstractVmInstance* inst = defaultValue->interpret(vm);
		releaser.registerInstance(inst);

		IAbstractVmInstanceSubstance* sub = inst != nullptr ? inst->getInstance() : nullptr;

		uint8_t instType = sub != nullptr ? sub->getInstType() : VmInstanceTypesConst::INST_NULL;

		if(instType == VmInstanceTypesConst::INST_NULL){
			modifyLog->setDefaultStr(nullptr);
		}
		else if(sub->instIsPrimitive()){
			PrimitiveReference* pr = dynamic_cast<PrimitiveReference*>(sub);
			const UnicodeString* str = pr->toString();

			modifyLog->setDefaultStr(new UnicodeString(str));
		}
		else if(VmInstanceTypesConst::INST_STRING == instType){
			VmStringInstance* strInst = dynamic_cast<VmStringInstance*>(sub);
			const UnicodeString* str = strInst->toString();

			modifyLog->setDefaultStr(new UnicodeString(str));
		}
		//else{ Not necessary
		//	TypeCastExceptionClassDeclare::throwException(vm, this);
		//	ExceptionInterrupt::interruptPoint(vm);
		//}
	}

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

	const UnicodeString* defstr = log->getDefaultValueStr();

	ColumnModifyContext* modifyContext = column->createModifyContextwithChange(this, defstr, false); __STP(modifyContext);
	modifyContext->setColumn(column);
	modifyContext->analyze();

	ColumnModifyContext::UniqueChage uchange = modifyContext->getUniqueChange();

	if(uchange == ColumnModifyContext::UniqueChage::TO_UNIQUE || (modifyContext->isUnique() && modifyContext->isTypeChanged())){
		IndexChecker checker(db, modifyContext);

		bool result = checker.checkUnique(table, column);
		if(!result){
			throw new CdbException(L"Can not set the column unique because of table data.", __FILE__, __LINE__);
		}

	}
}



} /* namespace alinous */
