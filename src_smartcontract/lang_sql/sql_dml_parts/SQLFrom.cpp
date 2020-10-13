/*
 * SQLFrom.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLFrom.h"
#include "lang_sql/sql_join_parts/TableIdentifier.h"
#include "lang_sql/sql/AbstractJoinPart.h"

namespace alinous {

SQLFrom::SQLFrom() : AbstractSQLPart(CodeElement::SQL_PART_FROM) {
	this->tableId = nullptr;
}

SQLFrom::~SQLFrom() {
	delete this->tableId;
}

void SQLFrom::setTable(AbstractJoinPart* tableId) noexcept {
	this->tableId = tableId;
}

AbstractJoinPart* SQLFrom::getTablePart() const noexcept {
	return this->tableId;
}

int SQLFrom::binarySize() const {
	checkNotNull(this->tableId);

	int total = sizeof(uint16_t);
	total += this->tableId->binarySize();

	return total;
}

void SQLFrom::toBinary(ByteBuffer* out) {
	checkNotNull(this->tableId);

	out->putShort(CodeElement::SQL_PART_FROM);
	this->tableId->toBinary(out);
}

void SQLFrom::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsJoinPart(element);
	this->tableId = dynamic_cast<AbstractJoinPart*>(element);
}

} /* namespace alinous */
