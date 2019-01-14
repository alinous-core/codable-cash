/*
 * TransactionId.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "bc_base/TransactionId.h"

#include "base_io/ByteBuffer.h"
#include "base/StackRelease.h"

namespace codablecash {

TransactionId::TransactionId() {
	this->id = nullptr;
}

TransactionId::TransactionId(const TransactionId& inst) {
	const ByteBuffer* buff = inst.id;
	this->id = ByteBuffer::wrapWithEndian(buff->array(), buff->capacity(), true);
}

TransactionId::TransactionId(const char* binary, int length) {
	this->id = ByteBuffer::wrapWithEndian((const uint8_t*)binary, length, true);
}

TransactionId::~TransactionId() {
	delete this->id;
}

int TransactionId::size() const noexcept {
	return this->id->capacity();
}

const char* TransactionId::toArray() const noexcept {
	return (const char*)this->id->array();
}

int codablecash::TransactionId::binarySize() const {
	int total = sizeof(int32_t);
	total += this->id->capacity();

	return total;
}

void codablecash::TransactionId::toBinary(ByteBuffer* out) const {
	int cap = this->id->capacity();
	out->putInt(cap);
	out->put(this->id->array(), cap);
}

TransactionId* TransactionId::fromBinary(ByteBuffer* in) {
	TransactionId* trxId = new TransactionId();

	int cap = in->getInt();

	uint8_t* buff = new uint8_t[cap];
	StackArrayRelease<uint8_t> __st_buff(buff);

	in->get(buff, cap);

	trxId->id = ByteBuffer::wrapWithEndian(buff, cap, true);
	trxId->id->position(0);

	return trxId;
}

} /* namespace codablecash */
