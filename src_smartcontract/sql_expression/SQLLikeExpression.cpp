/*
 * SQLLikeExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLLikeExpression.h"
#include "sql_expression/SQLLiteral.h"

namespace alinous {

SQLLikeExpression::SQLLikeExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_LIKE) {
	this->left = nullptr;
	this->right = nullptr;
	this->escape = nullptr;
}

SQLLikeExpression::~SQLLikeExpression() {
	delete this->left;
	delete this->right;
	delete this->escape;
}

void SQLLikeExpression::setLeft(AbstractSQLExpression* left) noexcept {
	this->left = left;
}

void SQLLikeExpression::setRight(SQLLiteral* right) noexcept {
	this->right = right;
}

void SQLLikeExpression::setEscape(SQLLiteral* escape) noexcept {
	this->escape = escape;
}

} /* namespace alinous */

int alinous::SQLLikeExpression::binarySize() const {
}

void alinous::SQLLikeExpression::toBinary(ByteBuffer* out) {
}

void alinous::SQLLikeExpression::fromBinary(ByteBuffer* in) {
}
