/*
 * SQLHaving.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLHaving.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLHaving::SQLHaving() : AbstractSQLPart(CodeElement::SQL_PART_HAVING) {
	this->exp = nullptr;
}

SQLHaving::~SQLHaving() {
	delete this->exp;
}

void alinous::SQLHaving::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLHaving::binarySize() const {
}

void SQLHaving::toBinary(ByteBuffer* out) {
}

void SQLHaving::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
