/*
 * CdbTableColumn.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "table/CdbTableColumn.h"

#include "engine/CdbOid.h"

#include "base/UnicodeString.h"

#include "transaction/SchemaObjectIdPublisher.h"

#include "base_io/ByteBuffer.h"


namespace codablecash {

CdbTableColumn::CdbTableColumn(uint64_t oid) {
	this->oid = new CdbOid(oid);
	this->name = nullptr;
	this->type = 0;
	this->length = 0;
	this->notnull = false;
	this->unique = false;
	this->defaultValue = nullptr;
}

CdbTableColumn::~CdbTableColumn() {
	delete this->oid;
	delete this->name;
	delete this->defaultValue;
}

const CdbOid* CdbTableColumn::getOid() const noexcept {
	return this->oid;
}

void CdbTableColumn::setName(const UnicodeString* name) noexcept {
	this->name = new UnicodeString(name);
}

void CdbTableColumn::setType(uint8_t type, int length) noexcept {
	this->type = type;
	this->length = length;
}

void CdbTableColumn::setAttributes(bool notnull, bool unique) noexcept {
	this->notnull = notnull;
	this->unique = unique;
}

void CdbTableColumn::setDefaultValue(const UnicodeString* defaultValue) noexcept {
	if(defaultValue != nullptr){
		this->defaultValue = new UnicodeString(defaultValue);
	}
}

void CdbTableColumn::assignNewOid(SchemaObjectIdPublisher* publisher) {
	uint64_t oid = publisher->newOid();
	setOid(oid);
}

void CdbTableColumn::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}


int CdbTableColumn::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint8_t);
	total += sizeof(uint64_t); // oid

	total += stringSize(this->name);

	total += sizeof(uint8_t);//uint8_t type;
	total += sizeof(uint32_t);//int length;
	total += sizeof(uint8_t);//bool notnull;
	total += sizeof(uint8_t);//bool unique;

	bool bl = this->defaultValue != nullptr;
	total += sizeof(uint8_t);
	if(bl){
		total += stringSize(this->defaultValue);
	}
	//UnicodeString* defaultValue;

	return total;
}

void CdbTableColumn::toBinary(ByteBuffer* out) const {
	checkNotNull(this->name);

	out->put(CdbTableColumn::CDB_OBJ_TYPE);
	out->putLong(this->oid->getOid());

	putString(out, this->name);

	out->put(this->type);
	out->putInt(this->length);
	out->put(this->notnull);
	out->put(this->unique);

	bool bl = this->defaultValue != nullptr;
	out->put(bl ? 1 : 0);
	if(bl){
		putString(out, this->defaultValue);
	}
}

void CdbTableColumn::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	this->type = in->get();
	this->length = in->getInt();
	this->notnull = in->get() > 0;
	this->unique = in->get() > 0;

	bool bl = in->get() > 0;
	if(bl){
		this->defaultValue = getString(in);
	}
}


} /* namespace codablecash */
