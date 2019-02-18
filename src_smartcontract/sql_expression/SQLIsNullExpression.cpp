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
}

SQLIsNullExpression::~SQLIsNullExpression() {
	delete this->exp;
}

void SQLIsNullExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
