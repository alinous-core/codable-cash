/*
 * SQLNotExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLNotExpression.h"

namespace alinous {

SQLNotExpression::SQLNotExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_NOT) {
	this->exp = nullptr;
}

SQLNotExpression::~SQLNotExpression() {
	delete this->exp;
}

void SQLNotExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */

int alinous::SQLNotExpression::binarySize() const {
}

void alinous::SQLNotExpression::toBinary(ByteBuffer* out) {
}

void alinous::SQLNotExpression::fromBinary(ByteBuffer* in) {
}
