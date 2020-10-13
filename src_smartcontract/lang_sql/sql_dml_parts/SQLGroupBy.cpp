/*
 * SQLGroupBy.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLGroupBy.h"
#include "lang_sql/sql_dml_parts/SQLColumnsList.h"
#include "lang_sql/sql_dml_parts/SQLHaving.h"

namespace alinous {

SQLGroupBy::SQLGroupBy() : AbstractSQLPart(CodeElement::SQL_PART_GROUP_BY) {
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

int SQLGroupBy::binarySize() const {
	checkNotNull(this->list);

	int total = sizeof(uint16_t);
	total += this->list->binarySize();

	total += sizeof(uint8_t);
	if(this->having != nullptr){
		total += this->having->binarySize();
	}

	return total;
}

void SQLGroupBy::toBinary(ByteBuffer* out) {
	checkNotNull(this->list);

	out->putShort(CodeElement::SQL_PART_GROUP_BY);
	this->list->toBinary(out);

	out->put(this->having != nullptr ? 1 : 0);
	if(this->having != nullptr){
		this->having->toBinary(out);
	}
}

void SQLGroupBy::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_PART_COLUMN_LIST);
	this->list = dynamic_cast<SQLColumnsList*>(element);

	int8_t bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkKind(element, CodeElement::SQL_PART_HAVING);
		this->having = dynamic_cast<SQLHaving*>(element);
	}
}

} /* namespace alinous */
