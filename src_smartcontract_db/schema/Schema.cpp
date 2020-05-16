/*
 * Schema.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "schema/Schema.h"

#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"

#include "engine/CdbOid.h"


namespace codablecash {

Schema::Schema(uint64_t oid) {
	this->name = nullptr;
	this->oid = new CdbOid(oid);
}

Schema::~Schema() {
	delete this->name;
	delete this->oid;
}

void Schema::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}

void Schema::setName(UnicodeString* name) noexcept {
	this->name = name;
}

int Schema::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint8_t);
	total += sizeof(uint64_t); // oid

	total += stringSize(this->name);

	return total;
}

void Schema::toBinary(ByteBuffer* out) const {
	checkNotNull(this->name);

	out->put(Schema::CDB_OBJ_TYPE);
	out->putLong(this->oid->getOid());

	putString(out, this->name);
}

void Schema::fromBinary(ByteBuffer* in) {
	this->name = getString(in);
}


} /* namespace codablecash */
