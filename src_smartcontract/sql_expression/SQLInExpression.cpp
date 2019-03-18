/*
 * SQLInExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLInExpression.h"
#include "sql_expression/SQLExpressionList.h"

namespace alinous {

SQLInExpression::SQLInExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_IN) {
	this->left = nullptr;
	this->list = nullptr;
}

SQLInExpression::~SQLInExpression() {
	delete this->left;
	delete this->list;
}

void SQLInExpression::setLeft(AbstractSQLExpression* left) noexcept {
	this->left = left;
}

void SQLInExpression::setList(SQLExpressionList* list) noexcept {
	this->list = list;
}

} /* namespace alinous */

int alinous::SQLInExpression::binarySize() const {
}

void alinous::SQLInExpression::toBinary(ByteBuffer* out) {
}

void alinous::SQLInExpression::fromBinary(ByteBuffer* in) {
}
