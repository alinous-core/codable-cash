/*
 * SQLLimitOffset.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLLimitOffset.h"
#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {

SQLLimitOffset::SQLLimitOffset() : AbstractSQLPart(CodeElement::SQL_PART_LIMIT_OFFSET) {
	this->limit = nullptr;
	this->offset = nullptr;
}

SQLLimitOffset::~SQLLimitOffset() {
	delete this->limit;
	delete this->offset;
}

void SQLLimitOffset::setLimit(AbstractSQLExpression* limit) noexcept {
	this->limit = limit;
}

void SQLLimitOffset::setOffset(AbstractSQLExpression* offset) noexcept {
	this->offset = offset;
}

int SQLLimitOffset::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint8_t);
	if(this->limit != nullptr){
		total += this->limit->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->offset != nullptr){
		total += this->offset->binarySize();
	}

	return total;
}

void SQLLimitOffset::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_PART_LIMIT_OFFSET);

	out->put(this->limit != nullptr ? 1 : 0);
	if(this->limit != nullptr){
		this->limit->toBinary(out);
	}

	out->put(this->offset != nullptr ? 1 : 0);
	if(this->offset != nullptr){
		this->offset->toBinary(out);
	}
}

void SQLLimitOffset::fromBinary(ByteBuffer* in) {
	int8_t bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkIsSQLExp(element);
		this->limit = dynamic_cast<AbstractSQLExpression*>(element);
	}

	bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkIsSQLExp(element);
		this->offset = dynamic_cast<AbstractSQLExpression*>(element);
	}
}

} /* namespace alinous */
