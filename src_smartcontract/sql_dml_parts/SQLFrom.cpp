/*
 * SQLFrom.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLFrom.h"
#include "sql_join_parts/TableIdentifier.h"
#include "sql/AbstractJoinPart.h"

namespace alinous {

SQLFrom::SQLFrom() {
	this->tableId = nullptr;
}

SQLFrom::~SQLFrom() {
	delete this->tableId;
}

void SQLFrom::setTable(AbstractJoinPart* tableId) noexcept {
	this->tableId = tableId;
}

int SQLFrom::binarySize() const {
}

void SQLFrom::toBinary(ByteBuffer* out) {
}

void SQLFrom::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
