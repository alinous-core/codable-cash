/*
 * SQLIsNullExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLIsNullExpression.h"

namespace alinous {

SQLIsNullExpression::SQLIsNullExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_IS_NULL) {
	this->exp = nullptr;
	this->notnull = false;
}

SQLIsNullExpression::~SQLIsNullExpression() {
	delete this->exp;
}

void SQLIsNullExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

void SQLIsNullExpression::setNotNull(bool notnull) noexcept {
	this->notnull = notnull;
}

} /* namespace alinous */

int alinous::SQLIsNullExpression::binarySize() const {
}

void alinous::SQLIsNullExpression::toBinary(ByteBuffer* out) {
}

void alinous::SQLIsNullExpression::fromBinary(ByteBuffer* in) {
}
