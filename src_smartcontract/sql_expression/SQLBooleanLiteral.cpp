/*
 * SQLBooleanLiteral.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLBooleanLiteral.h"

namespace alinous {

SQLBooleanLiteral::SQLBooleanLiteral() : AbstractSQLExpression(CodeElement::SQL_EXP_BOOL_LITERAL) {
	this->value = false;
}

SQLBooleanLiteral::~SQLBooleanLiteral() {
}

void SQLBooleanLiteral::setValue(bool value) noexcept {
	this->value = value;
}

} /* namespace alinous */
