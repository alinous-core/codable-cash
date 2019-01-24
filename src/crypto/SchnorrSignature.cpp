/*
 * SchnorrSignature.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "crypto/SchnorrSignature.h"
#include "numeric/BigInteger.h"

namespace codablecash {

using namespace std;

SchnorrSignature::SchnorrSignature(const BigInteger& e, const BigInteger& y) {
	this->e = new BigInteger(e);
	this->y = new BigInteger(y);
}

SchnorrSignature::~SchnorrSignature() {
	delete this->e;
	delete this->y;
}

} /* namespace codablecash */
