/*
 * SQLWhere.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLWhere.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLWhere::SQLWhere() {
	this->exp = nullptr;
}

SQLWhere::~SQLWhere() {
	delete this->exp;
}

void alinous::SQLWhere::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
