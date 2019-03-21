/*
 * SQLColumnsList.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLColumnsList.h"
#include "sql_expression/SQLColumnIdentifier.h"

namespace alinous {

SQLColumnsList::SQLColumnsList() : AbstractSQLPart(CodeElement::SQL_PART_COLUMN_LIST) {
}

SQLColumnsList::~SQLColumnsList() {
	this->list.deleteElements();
}

void SQLColumnsList::addColumn(SQLColumnIdentifier* colId) noexcept {
	this->list.addElement(colId);
}

int SQLColumnsList::binarySize() const {
}

void SQLColumnsList::toBinary(ByteBuffer* out) {
}

void SQLColumnsList::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
