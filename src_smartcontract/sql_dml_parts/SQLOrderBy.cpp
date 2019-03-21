/*
 * SQLOrderBy.cpp
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLOrderBy.h"
#include "sql_dml_parts/SQLColumnsList.h"

namespace alinous {

SQLOrderBy::SQLOrderBy() : AbstractSQLPart(CodeElement::SQL_PART_ORDER_BY) {
	this->list = nullptr;
}

SQLOrderBy::~SQLOrderBy() {
	delete this->list;
}

void SQLOrderBy::setList(SQLColumnsList* list) noexcept {
	this->list = list;
}

int SQLOrderBy::binarySize() const {
}

void SQLOrderBy::toBinary(ByteBuffer* out) {
}

void SQLOrderBy::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
