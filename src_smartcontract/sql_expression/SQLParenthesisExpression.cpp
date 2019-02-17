/*
 * SQLParenthesisExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLParenthesisExpression.h"

namespace alinous {

SQLParenthesisExpression::SQLParenthesisExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_PARENTHESIS) {
	this->exp = nullptr;
}

SQLParenthesisExpression::~SQLParenthesisExpression() {
	delete this->exp;
}

void SQLParenthesisExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
