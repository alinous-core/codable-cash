/*
 * InsertStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/InsertStatement.h"

#include "sql_dml_parts/SQLColumnsList.h"
#include "sql_expression/SQLExpressionList.h"
#include "sql_join_parts/TableIdentifier.h"

#include "vm_trx/VmTransactionHandler.h"

#include "vm/VirtualMachine.h"

#include "transaction_log/InsertLog.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_analyze_sql/AnalyzedInsertColumnList.h"
#include "sc_analyze_sql/AnalyzedInsertColumn.h"

#include "schema/SchemaManager.h"

#include "sql_expression/SQLColumnIdentifier.h"

#include "table/CdbTable.h"

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "vm_ctrl/ExecControlManager.h"

#include "table_record/CdbRecord.h"
#include "table_record/CdbTableIdentifier.h"

#include "instance_gc/StackFloatingVariableHandler.h"
#include "instance_gc/GcManager.h"

#include "sql/AbstractSQLExpression.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/AbstractVmInstance.h"

#include "table_record_value/AbstractCdbValue.h"
#include "table_record_value/VmInstanceValueConverter.h"

using namespace codablecash;

namespace alinous {

InsertStatement::InsertStatement() : AbstractSQLStatement(CodeElement::DML_STMT_INSERT) {
	this->tableId = nullptr;
	this->columns = nullptr;
	this->expList = nullptr;
	this->schemaVersion = 0;
	this->analyzedColumns = nullptr;
	this->tableIdentifier = nullptr;
}

InsertStatement::~InsertStatement() {
	delete this->tableId;
	delete this->columns;
	delete this->expList;
	delete this->analyzedColumns;
	delete this->tableIdentifier;
}

void InsertStatement::preAnalyze(AnalyzeContext* actx) {
	this->tableId->setParent(this);
	this->tableId->preAnalyze(actx);

	if(this->columns != nullptr){
		this->columns->setParent(this);
	}

	this->expList->setParent(this);
	this->expList->preAnalyze(actx);
}

void InsertStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->tableId->analyzeTypeRef(actx);
	this->expList->analyzeTypeRef(actx);
}

void InsertStatement::analyze(AnalyzeContext* actx) {
	this->tableId->analyze(actx);
	this->expList->analyze(actx);

	if(this->columns != nullptr){
		int expSize = this->expList->numExpressions();
		int colSize = this->columns->numColumns();
		if(expSize != colSize){
			actx->addValidationError(ValidationError::SQL_INSERT_VALUES_NUMBERS, this, L"Number of columns and values must be same.", {});
		}
	}

}

void InsertStatement::init(VirtualMachine* vm) {
	this->tableId->init(vm);
	this->expList->init(vm);
}

void InsertStatement::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	VmTransactionHandler* trxHandler = vm->getTransactionHandler();
	ExecControlManager* execCtrl = vm->getCtrl();

	uint64_t currentVersion = trxHandler->getSchemaObjectVersionId();
	if(currentVersion > this->schemaVersion){
		updateSchemaInfo(vm, trxHandler);
		if(execCtrl->isExceptionThrown()){
			return;
		}

		this->schemaVersion = currentVersion;
	}

	// make record
	CdbRecord* record = new CdbRecord();

	int colSize = this->analyzedColumns->size();
	record->initNullColumns(colSize);

	for(int i = 0; i != colSize; ++i){
		AnalyzedInsertColumn* col = this->analyzedColumns->get(i);
		int pos = col->getPosition();

		AbstractSQLExpression* exp = this->expList->getExpression(i);
		AbstractVmInstance* inst = exp->interpret(vm);
		releaser.registerInstance(inst);

		IAbstractVmInstanceSubstance* substance = inst != nullptr ? inst->getInstance() : nullptr;

		uint8_t targetCdbColumnType = col->getCdbColumnType();

		AbstractCdbValue* value = VmInstanceValueConverter::toCdbValue(substance, targetCdbColumnType);
		record->setValue(value, pos);
	}

	InsertLog* cmd = new InsertLog();
	cmd->setTable(new CdbTableIdentifier(*this->tableIdentifier));
	cmd->addRecord(record);

	trxHandler->insert(cmd);
}

void InsertStatement::updateSchemaInfo(VirtualMachine* vm, VmTransactionHandler* trxHandler) {
	delete this->analyzedColumns;
	this->analyzedColumns = new AnalyzedInsertColumnList();

	delete this->tableIdentifier;
	this->tableIdentifier = new CdbTableIdentifier();

	const UnicodeString* schema = this->tableId->getSchema();
	const UnicodeString* tableName = this->tableId->getTableName();
	if(schema == nullptr){
		schema = vm->getCurrentSchema();
	}

	this->tableIdentifier->setSchema(new UnicodeString(schema));
	this->tableIdentifier->setTable(new UnicodeString(tableName));

	CdbTable* table = trxHandler->getTable(schema, tableName);
	if(table == nullptr){
		UnicodeString errMsg(L"Table does not exists.");
		DatabaseExceptionClassDeclare::throwException(&errMsg, vm, this);
		return;
	}

	if(this->columns == nullptr){
		updateSchemaInfoWithNoColumnSpec(table, vm, trxHandler);
		return;
	}

	const ArrayList<SQLColumnIdentifier>* list = this->columns->getList();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		SQLColumnIdentifier* colId = list->get(i);
		const UnicodeString* colName = colId->getColumnName();

		CdbTableColumn* col = table->getColumn(colName);
		if(col == nullptr){
			UnicodeString errMsg(L"Column does not exists.");
			DatabaseExceptionClassDeclare::throwException(&errMsg, vm, this);
			return;
		}

		AnalyzedInsertColumn* acol = new AnalyzedInsertColumn(col);
		this->analyzedColumns->addAnalyzedInsertColumn(acol);
	}
}

void InsertStatement::updateSchemaInfoWithNoColumnSpec(CdbTable* table, VirtualMachine* vm, VmTransactionHandler* trxHandler) {
	int maxLoop = this->expList->numExpressions();
	int tableColSize = table->getColumns()->size();

	if(tableColSize < maxLoop){
		UnicodeString errMsg(L"Column number is too many.");

		DatabaseExceptionClassDeclare::throwException(&errMsg, vm, this);
		return;
	}

	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = table->getColumn(i);

		AnalyzedInsertColumn* acol = new AnalyzedInsertColumn(col);
		this->analyzedColumns->addAnalyzedInsertColumn(acol);
	}
}

void InsertStatement::setTable(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

void InsertStatement::setColumns(SQLColumnsList* columns) noexcept {
	this->columns = columns;
}

void InsertStatement::setExpressionList(SQLExpressionList* expList) noexcept {
	this->expList = expList;
}

int InsertStatement::binarySize() const {
	checkNotNull(this->tableId);
	checkNotNull(this->expList);

	int total = sizeof(uint16_t);
	total += this->tableId->binarySize();

	total += sizeof(uint8_t);
	if(this->columns != nullptr){
		total += this->columns->binarySize();
	}

	total += this->expList->binarySize();

	return total;
}

void InsertStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->tableId);
	checkNotNull(this->expList);

	out->putShort(CodeElement::DML_STMT_INSERT);
	this->tableId->toBinary(out);

	out->put(this->columns != nullptr ? 1 : 0);
	if(this->columns != nullptr){
		this->columns->toBinary(out);
	}

	this->expList->toBinary(out);
}

void InsertStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_TABLE_ID);
	this->tableId = dynamic_cast<TableIdentifier*>(element);

	int8_t bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkKind(element, CodeElement::SQL_PART_COLUMN_LIST);
		this->columns = dynamic_cast<SQLColumnsList*>(element);
	}

	element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_EXP_LIST);
	this->expList = dynamic_cast<SQLExpressionList*>(element);
}

} /* namespace alinous */
