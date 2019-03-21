/*
 * SQLWhere.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLWhere.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLWhere::SQLWhere() : AbstractSQLPart(CodeElement::SQL_PART_WHERE) {
	this->exp = nullptr;
}

SQLWhere::~SQLWhere() {
	delete this->exp;
}

void alinous::SQLWhere::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLWhere::binarySize() const {
}

void SQLWhere::toBinary(ByteBuffer* out) {
}

void SQLWhere::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
