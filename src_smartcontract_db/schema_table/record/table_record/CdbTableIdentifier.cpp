/*
 * CdbTableIdentifier.cpp
 *
 *  Created on: 2020/05/29
 *      Author: iizuka
 */

#include "schema_table/record/table_record/CdbTableIdentifier.h"

#include "base/UnicodeString.h"

#include "schema_table/schema/SchemaManager.h"

#include "base_io/ByteBuffer.h"


namespace codablecash {

codablecash::CdbTableIdentifier::CdbTableIdentifier(const CdbTableIdentifier& inst) {
	this->schema = new UnicodeString(inst.schema);
	this->table = new UnicodeString(inst.table);
}

CdbTableIdentifier::CdbTableIdentifier() {
	this->schema = new UnicodeString(&SchemaManager::PUBLIC);
	this->table = nullptr;
}

codablecash::CdbTableIdentifier::CdbTableIdentifier(const wchar_t* scheme, const wchar_t* table) {
	this->schema = new UnicodeString(scheme);
	this->table = new UnicodeString(table);
}


CdbTableIdentifier::~CdbTableIdentifier() {
	delete this->schema;
	delete this->table;
}

void CdbTableIdentifier::setSchema(UnicodeString* schema) noexcept {
	delete this->schema;
	this->schema = schema;
}

void CdbTableIdentifier::setTable(UnicodeString* table) noexcept {
	delete this->table;
	this->table = table;
}

int CdbTableIdentifier::binarySize() const {
	checkNotNull(this->schema);
	checkNotNull(this->table);

	int total = stringSize(this->schema);
	total += stringSize(this->table);

	return total;
}

void CdbTableIdentifier::toBinary(ByteBuffer* out) const {
	checkNotNull(this->schema);
	checkNotNull(this->table);

	putString(out, this->schema);
	putString(out, this->table);
}

CdbTableIdentifier* CdbTableIdentifier::fromBinary(ByteBuffer* in) {
	CdbTableIdentifier* id = new CdbTableIdentifier();

	UnicodeString* str = id->getString(in);
	id->setSchema(str);

	str = id->getString(in);
	id->setTable(str);

	return id;
}

} /* namespace codablecash */
