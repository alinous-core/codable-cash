/*
 * SchnorrKeyPair.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "crypto/SchnorrKeyPair.h"
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

} /* namespace codablecash */
