/*
 * SQLLimitOffset.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLLimitOffset.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLLimitOffset::SQLLimitOffset() {
	this->limit = nullptr;
	this->offset = nullptr;
}

SQLLimitOffset::~SQLLimitOffset() {
	delete this->limit;
	delete this->offset;
}

void SQLLimitOffset::setLimit(AbstractSQLExpression* limit) noexcept {
	this->limit = limit;
}

void SQLLimitOffset::setOffset(AbstractSQLExpression* offset) noexcept {
	this->offset = offset;
}

} /* namespace alinous */
