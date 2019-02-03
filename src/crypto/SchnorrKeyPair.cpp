/*
 * SchnorrKeyPair.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "crypto/SchnorrKeyPair.h"

#include "base_io/ByteBuffer.h"
#include "base/StackRelease.h"
#include "numeric/BigInteger.h"

namespace codablecash {

SchnorrKeyPair::SchnorrKeyPair() {
	this->secretKey = nullptr;
	this->publicKey = nullptr;
}

SchnorrKeyPair::SchnorrKeyPair(const BigInteger& secretKey, const BigInteger& publicKey) {
	this->secretKey = new BigInteger(secretKey);
	this->publicKey = new BigInteger(publicKey);
}

SchnorrKeyPair::~SchnorrKeyPair() {
	delete this->secretKey;
	delete this->publicKey;
}

IKeyPair* SchnorrKeyPair::clone() const noexcept {
	return new SchnorrKeyPair(*this->secretKey, *this->publicKey);
}

int SchnorrKeyPair::binarySize() const {
	ByteBuffer* p = this->publicKey->toBinary(); __STP(p);

	return sizeof(int8_t) + sizeof(int16_t) + p->capacity();
}

void SchnorrKeyPair::toBinary(ByteBuffer* out) const {
	out->put(IKeyPair::PAIR_SCHNORR);

	ByteBuffer* p = this->publicKey->toBinary(); __STP(p);

	out->putShort(p->capacity());
	out->put(p);
}

void SchnorrKeyPair::fromBinary(ByteBuffer* in) {
	int length = in->getShort();
	int position = in->position();

	this->publicKey = BigInteger::fromBinary((const char*)in->array() + position, length);

	in->position(position + length);
}

} /* namespace codablecash */
