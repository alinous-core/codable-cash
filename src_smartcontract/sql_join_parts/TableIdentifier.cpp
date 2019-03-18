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

} /* namespace alinous */

int alinous::TableIdentifier::binarySize() const {
}

void alinous::TableIdentifier::toBinary(ByteBuffer* out) {
}

void alinous::TableIdentifier::fromBinary(ByteBuffer* in) {
}
