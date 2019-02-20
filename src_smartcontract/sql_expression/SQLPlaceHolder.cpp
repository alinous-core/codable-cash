/*
 * SQLPlaceHolder.cpp
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#include "sql_expression/SQLPlaceHolder.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

SQLPlaceHolder::SQLPlaceHolder() : AbstractSQLExpression(CodeElement::SQL_EXP_PLACE_HOLDER) {
	this->exp = nullptr;
}

SQLPlaceHolder::~SQLPlaceHolder() {
	delete this->exp;
}

void SQLPlaceHolder::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
