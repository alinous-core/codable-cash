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
