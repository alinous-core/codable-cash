/*
 * SQLColumnIdentifier.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLColumnIdentifier.h"
#include "base/UnicodeString.h"

namespace alinous {

SQLColumnIdentifier::SQLColumnIdentifier() : AbstractSQLExpression(CodeElement::SQL_EXP_COLUMN_ID){
	this->schema = nullptr;
	this->tableName =nullptr;
	this->columnName =nullptr;
}

SQLColumnIdentifier::~SQLColumnIdentifier() {
	delete this->schema;
	delete this->tableName;
	delete this->columnName;
}

void SQLColumnIdentifier::setSchema(UnicodeString* schema) noexcept {
	this->schema = schema;
}

void SQLColumnIdentifier::setTableName(UnicodeString* tableName) noexcept {
	this->tableName = tableName;
}

void SQLColumnIdentifier::setColumnName(UnicodeString* columnName) noexcept {
	this->columnName = columnName;
}

int SQLColumnIdentifier::binarySize() const {
	checkNotNull(this->columnName);

	int total = sizeof(uint16_t);
	total += sizeof(uint8_t);
	if(this->schema != nullptr){
		total += stringSize(this->schema);
	}

	total += sizeof(uint8_t);
	if(this->tableName != nullptr){
		total += stringSize(this->tableName);
	}

	total += stringSize(this->columnName);

	return total;
}

void SQLColumnIdentifier::toBinary(ByteBuffer* out) {
	checkNotNull(this->columnName);

	out->putShort(CodeElement::SQL_EXP_COLUMN_ID);

	out->put(this->schema != nullptr ? 1 : 0);
	if(this->schema != nullptr){
		putString(out, this->schema);
	}

	out->put(this->tableName != nullptr ? 1 : 0);
	if(this->tableName != nullptr){
		putString(out, this->tableName);
	}

	putString(out, this->columnName);
}

void SQLColumnIdentifier::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	if(bl == 1){
		this->schema = getString(in);
	}
	bl = in->get();
	if(bl == 1){
		this->tableName = getString(in);
	}
	this->columnName = getString(in);
}

} /* namespace alinous */
