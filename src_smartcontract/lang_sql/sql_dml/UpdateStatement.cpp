/*
 * UpdateStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_dml/UpdateStatement.h"
#include "lang_sql/sql_dml_parts/SQLWhere.h"
#include "lang_sql/sql_dml_parts/SQLSet.h"

#include "lang_sql/sql_join_parts/TableIdentifier.h"

namespace alinous {

UpdateStatement::UpdateStatement() : AbstractSQLStatement(CodeElement::DML_STMT_UPDATE) {
	this->tableId = nullptr;
	this->set = nullptr;
	this->where = nullptr;
}

UpdateStatement::~UpdateStatement() {
	delete this->tableId;
	delete this->set;
	delete this->where;
}

void UpdateStatement::preAnalyze(AnalyzeContext* actx) {

}

void UpdateStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void UpdateStatement::analyze(AnalyzeContext* actx) {

}

void UpdateStatement::setTable(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

void UpdateStatement::setSet(SQLSet* set) noexcept {
	this->set = set;
}

void UpdateStatement::setWhere(SQLWhere* where) noexcept {
	this->where = where;
}

int UpdateStatement::binarySize() const {
	checkNotNull(this->tableId);
	checkNotNull(this->set);

	int total = sizeof(uint16_t);
	total += this->tableId->binarySize();
	total += this->set->binarySize();

	total += sizeof(uint8_t);
	if(this->where != nullptr){
		total += this->where->binarySize();
	}

	return total;
}

void UpdateStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->tableId);
	checkNotNull(this->set);

	out->putShort(CodeElement::DML_STMT_UPDATE);
	this->tableId->toBinary(out);
	this->set->toBinary(out);

	out->put(this->where != nullptr ? 1 : 0);
	if(this->where != nullptr){
		this->where->toBinary(out);
	}
}

void UpdateStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_TABLE_ID);
	this->tableId = dynamic_cast<TableIdentifier*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_PART_SET);
	this->set = dynamic_cast<SQLSet*>(element);

	int8_t bl = in->get();
	if(bl == 1){
		 element = createFromBinary(in);
		 checkKind(element, CodeElement::SQL_PART_WHERE);
		 this->where = dynamic_cast<SQLWhere*>(element);
	}
}

void UpdateStatement::interpret(VirtualMachine* vm) {
	// FIXME SQL statement
}

} /* namespace alinous */
