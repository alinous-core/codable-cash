/*
 * Nonce.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "Nonce.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

Nonce::Nonce(uint32_t targetDiff, uint32_t diff) {
	this->targetDiff = targetDiff;
	this->diff = diff;
}

Nonce::~Nonce() {
}

int Nonce::binarySize() const {
	return sizeof(uint32_t) * 2;
}

void Nonce::toBinary(ByteBuffer* out) const {
	out->putInt(this->targetDiff);
	out->putInt(this->diff);
}

Nonce* Nonce::fromBinary(ByteBuffer* in) {
	uint32_t targetDiff = in->getInt();
	uint32_t diff = in->getInt();
	return new Nonce(targetDiff, diff);
}

} /* namespace codablecash */
