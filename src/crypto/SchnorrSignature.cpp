/*
 * SchnorrSignature.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "SchnorrSignature.h"

namespace codablecash {

SchnorrSignature::SchnorrSignature(mpz_t e, mpz_t y) {
	mpz_init_set(this->e, e);
	mpz_init_set(this->y, y);
}

SchnorrSignature::~SchnorrSignature() {
	mpz_clear(this->e);
	mpz_clear(this->y);
}

} /* namespace codablecash */
