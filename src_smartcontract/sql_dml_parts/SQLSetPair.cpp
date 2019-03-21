/*
 * SQLSetPair.cpp
 *
 *  Created on: 2019/02/22
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLSetPair.h"

#include "sql_expression/SQLColumnIdentifier.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLSetPair::SQLSetPair() : AbstractSQLPart(CodeElement::SQL_PART_ST_PAIR) {
	this->colId = nullptr;
	this->exp = nullptr;
}

SQLSetPair::~SQLSetPair() {
	delete this->colId;
	delete this->exp;
}

void SQLSetPair::setColumn(SQLColumnIdentifier* colId) noexcept {
	this->colId = colId;
}

void SQLSetPair::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLSetPair::binarySize() const {
}

void SQLSetPair::toBinary(ByteBuffer* out) {
}

void SQLSetPair::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
