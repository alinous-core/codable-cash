/*
 * SQLFrom.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLFrom.h"
#include "sql_join_parts/TableIdentifier.h"

namespace alinous {

SQLFrom::SQLFrom() {
	this->tableId = nullptr;
}

SQLFrom::~SQLFrom() {
	delete this->tableId;
}

void SQLFrom::setTableId(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

} /* namespace alinous */
