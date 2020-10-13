/*
 * AbstractSQLExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {

AbstractSQLExpression::AbstractSQLExpression(int kind) : CodeElement(kind) {
	this->executable = true;
}

AbstractSQLExpression::~AbstractSQLExpression() {
}

bool AbstractSQLExpression::isExecutable() {
	return this->executable;
}

void AbstractSQLExpression::setExecutable(bool executable) noexcept {
	this->executable = executable;
}

} /* namespace alinous */
