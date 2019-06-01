/*
 * DeleteStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/DeleteStatement.h"

#include "sql_dml_parts/SQLFrom.h"
#include "sql_dml_parts/SQLWhere.h"

namespace alinous {

DeleteStatement::DeleteStatement() : AbstractSQLStatement(CodeElement::DML_STMT_DELETE) {
	this->from = nullptr;
	this->where = nullptr;
}

DeleteStatement::~DeleteStatement() {
	delete this->from;
	delete this->where;
}

void DeleteStatement::preAnalyze(AnalyzeContext* actx) {

}

void DeleteStatement::analyze(AnalyzeContext* actx) {

}

void DeleteStatement::setFrom(SQLFrom* from) noexcept {
	this->from = from;
}

void DeleteStatement::setWhere(SQLWhere* where) noexcept {
	this->where = where;
}

int DeleteStatement::binarySize() const {
	checkNotNull(this->from);

	int total = sizeof(uint16_t);
	total += this->from->binarySize();

	total += sizeof(uint8_t);
	if(this->where != nullptr){
		total += this->where->binarySize();
	}

	return total;
}

void DeleteStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->from);

	out->putShort(CodeElement::DML_STMT_DELETE);
	this->from->toBinary(out);

	out->put(this->where != nullptr ? 1 : 0);
	if(this->where != nullptr){
		this->where->toBinary(out);
	}
}

void DeleteStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_PART_FROM);
	this->from = dynamic_cast<SQLFrom*>(element);

	int8_t bl = in->get();
	if(bl == 1){
		 element = createFromBinary(in);
		 checkKind(element, CodeElement::SQL_PART_WHERE);
		 this->where = dynamic_cast<SQLWhere*>(element);
	}
}

} /* namespace alinous */
