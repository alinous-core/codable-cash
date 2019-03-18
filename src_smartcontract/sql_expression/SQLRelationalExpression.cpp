/*
 * SQLRelationalExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLRelationalExpression.h"

namespace alinous {

SQLRelationalExpression::SQLRelationalExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_RELATIONAL) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

SQLRelationalExpression::~SQLRelationalExpression() {
	delete this->left;
	delete this->right;
}

void SQLRelationalExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLRelationalExpression::setRight(AbstractSQLExpression* exp) noexcept {
	this->right = exp;
}

void SQLRelationalExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

} /* namespace alinous */

int alinous::SQLRelationalExpression::binarySize() const {
}

void alinous::SQLRelationalExpression::toBinary(ByteBuffer* out) {
}

void alinous::SQLRelationalExpression::fromBinary(ByteBuffer* in) {
}
