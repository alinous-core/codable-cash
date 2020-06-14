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
namespace alinous {

InsertStatement::InsertStatement() : AbstractSQLStatement(CodeElement::DML_STMT_INSERT) {
	this->tableId = nullptr;
	this->columns = nullptr;
	this->expList = nullptr;
}

InsertStatement::~InsertStatement() {
	delete this->tableId;
	delete this->columns;
	delete this->expList;
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
}

void InsertStatement::interpret(VirtualMachine* vm) {
	VmTransactionHandler* trxHandler = vm->getTransactionHandler();



	// FIXME SQL statement
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
