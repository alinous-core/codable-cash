/*
 * SQLExpressionList.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLExpressionList.h"

namespace alinous {

SQLExpressionList::SQLExpressionList() : AbstractSQLExpression(CodeElement::SQL_EXP_EXP_LIST) {
}

SQLExpressionList::~SQLExpressionList() {
	this->list.deleteElements();
}

void SQLExpressionList::addExpression(AbstractSQLExpression* exp) noexcept {
	this->list.addElement(exp);
}

} /* namespace alinous */

int alinous::SQLExpressionList::binarySize() const {
}

void alinous::SQLExpressionList::toBinary(ByteBuffer* out) {
}

void alinous::SQLExpressionList::fromBinary(ByteBuffer* in) {
}
