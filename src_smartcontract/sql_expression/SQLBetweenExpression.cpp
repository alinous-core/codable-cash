/*
 * SQLBetweenExpression.cpp
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#include "sql_expression/SQLBetweenExpression.h"

namespace alinous {

SQLBetweenExpression::SQLBetweenExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_BETWEEN) {
	this->left = nullptr;
	this->start = nullptr;
	this->end = nullptr;
}

SQLBetweenExpression::~SQLBetweenExpression() {
	delete this->left;
	delete this->start;
	delete this->end;
}

void SQLBetweenExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLBetweenExpression::setStart(AbstractSQLExpression* exp) noexcept {
	this->start = exp;
}

void SQLBetweenExpression::setEnd(AbstractSQLExpression* exp) noexcept {
	this->end = exp;
}

} /* namespace alinous */
