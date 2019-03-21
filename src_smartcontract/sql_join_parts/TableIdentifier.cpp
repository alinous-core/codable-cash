/*
 * TableIdentifier.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_join_parts/TableIdentifier.h"
#include "base/UnicodeString.h"


namespace alinous {

TableIdentifier::TableIdentifier() : AbstractJoinPart(CodeElement::SQL_EXP_TABLE_ID) {
	this->schema = nullptr;
	this->tableName =nullptr;
}

TableIdentifier::~TableIdentifier() {
	delete this->schema;
	delete this->tableName;
}

void TableIdentifier::setSchema(UnicodeString* schema) noexcept {
	this->schema = schema;
}

void TableIdentifier::setTableName(UnicodeString* tableName) noexcept {
	this->tableName = tableName;
}

int TableIdentifier::binarySize() const {
	checkNotNull(this->tableName);

	int total = sizeof(uint16_t);

	total += sizeof(uint8_t);
	if(this->schema != nullptr){
		total += stringSize(this->schema);
	}

	total += stringSize(this->tableName);

	return total;
}

void TableIdentifier::toBinary(ByteBuffer* out) {
	checkNotNull(this->tableName);

	out->putShort(CodeElement::SQL_EXP_TABLE_ID);

	out->put(this->schema != nullptr ? 1 : 0);
	if(this->schema != nullptr){
		putString(out, this->schema);
	}
	putString(out, this->tableName);
}

void TableIdentifier::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	if(bl == 1){
		this->schema = getString(in);
	}

	this->tableName = getString(in);
}

} /* namespace alinous */
