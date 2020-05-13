/*
 * SchemaBinary.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/SchemaBinary.h"

#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"


namespace codablecash {

SchemaBinary::SchemaBinary() {
	this->maxTransactionId = 0;
	this->maxObjectId = 0;
}

SchemaBinary::~SchemaBinary() {
	this->list.deleteElements();
}

void SchemaBinary::addSchemaName(const UnicodeString* name) noexcept {
	this->list.addElement(new UnicodeString(name));
}

int SchemaBinary::binarySize() const noexcept {
	int total = 0;

	total += sizeof(uint64_t) * 2;

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* name = this->list.get(i);

		total += stringSize(name);
	}

	return total;
}

void SchemaBinary::toBinary(ByteBuffer* out) const {
	out->putLong(this->maxTransactionId);
	out->putLong(this->maxObjectId);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* name = this->list.get(i);

		putString(out, name);
	}
}

void SchemaBinary::fromBinary(ByteBuffer* in) {
	this->maxTransactionId = in->getLong();
	this->maxObjectId = in->getLong();

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* name = getString(in);
		this->list.addElement(name);
	}
}

uint64_t SchemaBinary::newTransactionId() noexcept {
	this->maxTransactionId++;
	return this->maxTransactionId;
}

} /* namespace codablecash */
