/*
 * TableList.cpp
 *
 *  Created on: 2019/02/27
 *      Author: iizuka
 */

#include "sql_join_parts/TableList.h"
#include "sql_join_parts/TableIdentifier.h"

namespace alinous {

TableList::TableList() : AbstractJoinPart(CodeElement::SQL_EXP_TABLE_LIST) {
}

TableList::~TableList() {
	this->list.deleteElements();
}

void TableList::addTable(AbstractJoinPart* tableId) noexcept {
	this->list.addElement(tableId);
}

int TableList::binarySize() const {
}

void TableList::toBinary(ByteBuffer* out) {
}

void TableList::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
