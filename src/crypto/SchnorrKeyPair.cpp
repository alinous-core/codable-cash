/*
 * SchnorrKeyPair.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "SchnorrKeyPair.h"

namespace codablecash {

SchnorrKeyPair::SchnorrKeyPair(mpz_t secretKey, mpz_t publicKey) {
	mpz_init_set(this->secretKey, secretKey);
	mpz_init_set(this->publicKey, publicKey);
}

SchnorrKeyPair::~SchnorrKeyPair() {
	mpz_clear(this->secretKey);
	mpz_clear(this->publicKey);
}

} /* namespace codablecash */
