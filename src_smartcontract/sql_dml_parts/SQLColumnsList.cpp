/*
 * SQLColumnsList.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLColumnsList.h"
#include "sql_expression/SQLColumnIdentifier.h"

namespace alinous {

SQLColumnsList::SQLColumnsList() {
}

SQLColumnsList::~SQLColumnsList() {
	this->list.deleteElements();
}

void SQLColumnsList::addColumn(SQLColumnIdentifier* colId) noexcept {
	this->list.addElement(colId);
}

} /* namespace alinous */
