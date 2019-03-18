/*
 * SQLEqualityExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLEqualityExpression.h"

namespace alinous {

SQLEqualityExpression::SQLEqualityExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_EQUALITY) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

SQLEqualityExpression::~SQLEqualityExpression() {
	delete this->left;
	delete this->right;
}

void SQLEqualityExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLEqualityExpression::setRight(AbstractSQLExpression* exp) noexcept {
	this->right = exp;
}

void SQLEqualityExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

} /* namespace alinous */

int alinous::SQLEqualityExpression::binarySize() const {
}

void alinous::SQLEqualityExpression::toBinary(ByteBuffer* out) {
}

void alinous::SQLEqualityExpression::fromBinary(ByteBuffer* in) {
}
