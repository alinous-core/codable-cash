/*
 * TransactionId.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "bc_base/TransactionId.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

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

int codablecash::TransactionId::binarySize() const {
	// FIXME
}

void codablecash::TransactionId::toBinary(ByteBuffer* out) const {
	// FIXME
}

} /* namespace codablecash */
