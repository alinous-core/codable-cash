/*
 * SchnorrKeyPair.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "crypto/SchnorrKeyPair.h"

#include "base_io/ByteBuffer.h"
#include "numeric/BigInteger.h"

namespace codablecash {

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

ByteBuffer* SchnorrKeyPair::toBinary() const {
	ByteBuffer* p = this->publicKey->toBinary();
	ByteBuffer* s = this->secretKey->toBinary();

	p->put(s);

	delete s;

	return p;
}

} /* namespace codablecash */
