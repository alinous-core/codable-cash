/*
 * SQLGroupBy.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLGroupBy.h"
#include "sql_dml_parts/SQLColumnsList.h"
#include "sql_dml_parts/SQLHaving.h"

namespace alinous {

SQLGroupBy::SQLGroupBy() {
	this->list = nullptr;
	this->having = nullptr;
}

SQLGroupBy::~SQLGroupBy() {
	delete this->list;
	delete this->having;
}

void SQLGroupBy::setList(SQLColumnsList* list) noexcept {
	this->list = list;
}

void SQLGroupBy::setHaving(SQLHaving* having) noexcept {
	this->having = having;
}

} /* namespace alinous */
