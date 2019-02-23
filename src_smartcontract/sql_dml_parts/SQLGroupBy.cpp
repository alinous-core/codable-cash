/*
 * SQLGroupBy.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLGroupBy.h"

namespace alinous {

SQLGroupBy::SQLGroupBy() {
	this->having = nullptr;
}

SQLGroupBy::~SQLGroupBy() {
	delete this->having;
}

void SQLGroupBy::setHaving(SQLHaving* having) noexcept {
	this->having = having;
}

} /* namespace alinous */
