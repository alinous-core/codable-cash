/*
 * SQLOrderBy.cpp
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLOrderBy.h"
#include "lang_sql/sql_dml_parts/SQLColumnsList.h"

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
	checkNotNull(this->list);

	int total = sizeof(uint16_t);
	total += this->list->binarySize();

	return total;
}

void SQLOrderBy::toBinary(ByteBuffer* out) {
	checkNotNull(this->list);

	out->putShort(CodeElement::SQL_PART_ORDER_BY);
	this->list->toBinary(out);
}

void SQLOrderBy::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_PART_COLUMN_LIST);
	this->list = dynamic_cast<SQLColumnsList*>(element);
}

} /* namespace alinous */
