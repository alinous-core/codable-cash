/*
 * CreateTableStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl/CreateTableStatement.h"
#include "lang_sql/sql_ddl/DdlColumnDescriptor.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "base/Exception.h"

#include "schema_table/table/CdbTable.h"

#include "vm/VirtualMachine.h"

#include "trx/transaction_log/CreateTableLog.h"



#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "vm_trx/VmTransactionHandler.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "lang_sql/sql_ddl/ColumnTypeDescriptor.h"

#include "lang_sql/sql/AbstractSQLExpression.h"

#include "instance_ref/PrimitiveReference.h"


#include "instance_gc/StackFloatingVariableHandler.h"

#include "schema_table/schema/SchemaManager.h"

#include "engine/CdbException.h"

#include "engine/CodableDatabase.h"

#include "schema_table/table_record_value/CdbValueCaster.h"

#include "schema_table/table_record_value/AbstractCdbValue.h"
using codablecash::CdbValueCaster;
namespace alinous {

CreateTableStatement::CreateTableStatement() : AbstractSQLStatement(CodeElement::DDL_CREATE_TABLE) {
	this->name = nullptr;
	this->list = new ArrayList<DdlColumnDescriptor>();
	this->primaryKeys = new ArrayList<UnicodeString>();
}

CreateTableStatement::~CreateTableStatement() {
	delete this->name;

	this->list->deleteElements();
	delete this->list;

	this->primaryKeys->deleteElements();
	delete this->primaryKeys;
}

void CreateTableStatement::preAnalyze(AnalyzeContext* actx) {

}

void CreateTableStatement::analyzeTypeRef(AnalyzeContext* actx) {

}


void CreateTableStatement::analyze(AnalyzeContext* actx) {
	{
		int maxLoop = this->list->size();
		for(int i = 0; i != maxLoop; ++i){
			DdlColumnDescriptor* colDesc = this->list->get(i);
			colDesc->analyze(actx);
		}
	}

	if(this->primaryKeys->isEmpty()){
		actx->addValidationError(ValidationError::DB_NO_PRIMARY_KEY, this, L"Primary key is required.", {});
	}

	ArrayList<const UnicodeString, UnicodeString::ValueCompare> namelist;

	int maxLoop = this->list->size();
	for(int i = 0; i != maxLoop; ++i){
		DdlColumnDescriptor* colDesc = this->list->get(i);
		ColumnTypeDescriptor* typeDesc = colDesc->getColumnTypeDescriptor();

		const UnicodeString* nm = colDesc->getName();
		const UnicodeString* n = namelist.search(nm);
		if(n != nullptr){
			actx->addValidationError(ValidationError::DB_CREATE_TABLE_COLUMN_DUPLICATED_NAME, this, L"The column {0} is duplicated.", {nm});
		}
		namelist.addElement(nm);

		uint8_t type = typeDesc->toCdbValueType();
		if(type == 0){
			const UnicodeString* tname = typeDesc->getTypeName();
			actx->addValidationError(ValidationError::DB_TYPE_NOT_EXISTS, this, L"The type {0} does not exists.", {tname});
		}

		AbstractSQLExpression* lengthExp = typeDesc->getLengthExp();
		if(lengthExp != nullptr){
			AnalyzedType at = lengthExp->getType(actx);
			if(!at.isPrimitiveInteger()){
				const UnicodeString* tname = typeDesc->getTypeName();
				actx->addValidationError(ValidationError::DB_LENGTH_IS_NOT_INTEGER, this, L"The type {0}'s length must be integer value.", {tname});
			}
		}

	}
}

void CreateTableStatement::interpret(VirtualMachine* vm) {
	CreateTableLog* cmd = new CreateTableLog();

	VmTransactionHandler* handler = vm->getTransactionHandler();
	try{
		CdbTable* table = createTable(vm);
		cmd->setTable(table);

		validate(vm, cmd);
		handler->createTable(cmd);
	}
	catch(Exception* e){
		DatabaseExceptionClassDeclare::throwException(e->getMessage(), vm, this);
		delete e;
		delete cmd;
	}
}

void CreateTableStatement::validate(VirtualMachine* vm, CreateTableLog* cmd) {
	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	CdbTable* table = cmd->getTable();

	if(schemaManager->hasTable(table->getSchemaName(), table->getName())){
		throw new CdbException(L"Table already exists.", __FILE__, __LINE__);
	}
}


CdbTable* CreateTableStatement::createTable(VirtualMachine* vm) {
	StackFloatingVariableHandler releaser(vm->getGc());

	CdbTable* table = new CdbTable(0);
	StackRelease<CdbTable> __tableRelease(table);

	table->setName(new UnicodeString(this->name));

	int maxLoop = this->list->size();
	for(int i = 0; i != maxLoop; ++i){
		DdlColumnDescriptor* colDesc = this->list->get(i);
		ColumnTypeDescriptor* typeDesc = colDesc->getColumnTypeDescriptor();

		uint8_t type = typeDesc->toCdbValueType();
		const UnicodeString* name = colDesc->getName();

		AbstractSQLExpression* lengthExp = typeDesc->getLengthExp();
		int length = 0;
		if(lengthExp != nullptr){
			AbstractVmInstance* inst = lengthExp->interpret(vm);
			releaser.registerInstance(inst);
			PrimitiveReference* l = dynamic_cast<PrimitiveReference*>(inst);

			length = l->getIntValue();
		}

		const UnicodeString* defaultValue = nullptr;
		AbstractSQLExpression* defExp = colDesc->getDefaultValue();
		if(defExp != nullptr){
			AbstractVmInstance* inst = defExp->interpret(vm);
			releaser.registerInstance(inst);

			if(inst != nullptr){
				defaultValue = inst->toString();
			}
		}

		try{
			AbstractCdbValue* testValue = CdbValueCaster::convertFromString(defaultValue, type); __STP(testValue);
		}
		catch(Exception* e){
			throw e;
		}

		table->addColumn(0, name, type, length, colDesc->isNotNull(), colDesc->isUnique(), defaultValue);
	}

	__tableRelease.cancel();

	return table;
}

int CreateTableStatement::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);

	total += stringSize(this->name);

	total += sizeof(int32_t);
	int maxLoop = this->list->size();
	for(int i = 0; i != maxLoop; ++i){
		DdlColumnDescriptor* col = this->list->get(i);
		total += col->binarySize();
	}

	total += sizeof(int32_t);
	maxLoop = this->primaryKeys->size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* key = this->primaryKeys->get(i);
		total += stringSize(key);
	}

	return total;
}

void CreateTableStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_CREATE_TABLE);

	putString(out, this->name);

	int maxLoop = this->list->size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		DdlColumnDescriptor* col = this->list->get(i);
		col->toBinary(out);
	}

	maxLoop = this->primaryKeys->size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* key = this->primaryKeys->get(i);
		putString(out, key);
	}
}

void CreateTableStatement::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);

		DdlColumnDescriptor* col = dynamic_cast<DdlColumnDescriptor*>(element);
		this->list->addElement(col);
	}

	maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* key = getString(in);
		this->primaryKeys->addElement(key);
	}
}

void CreateTableStatement::addColumn(DdlColumnDescriptor* col) noexcept {
	this->list->addElement(col);
}

void CreateTableStatement::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void CreateTableStatement::addPrimaryKey(UnicodeString* key) noexcept {
	this->primaryKeys->addElement(key);
}

} /* namespace alinous */
