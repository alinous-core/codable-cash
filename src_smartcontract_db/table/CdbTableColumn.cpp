/*
 * CdbTableColumn.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "table/CdbTableColumn.h"

#include "engine/CdbOid.h"

#include "base/UnicodeString.h"

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
	this->defaultValue = new UnicodeString(defaultValue);
}


} /* namespace codablecash */
