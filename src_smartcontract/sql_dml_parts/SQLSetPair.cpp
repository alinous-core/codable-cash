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

SQLSetPair::SQLSetPair() {
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

} /* namespace alinous */

int alinous::SQLSetPair::binarySize() const {
}

void alinous::SQLSetPair::toBinary(ByteBuffer* out) {
}

void alinous::SQLSetPair::fromBinary(ByteBuffer* in) {
}
