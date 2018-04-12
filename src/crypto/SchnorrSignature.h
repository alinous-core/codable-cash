/*
 * SchnorrSignature.h
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#ifndef CRYPTO_SCHNORRSIGNATURE_H_
#define CRYPTO_SCHNORRSIGNATURE_H_

#include <gmp.h>

namespace codablecash {

class SchnorrSignature {
public:
	mpz_t e, y;

	SchnorrSignature(mpz_t e, mpz_t y);
	virtual ~SchnorrSignature();
};

} /* namespace codablecash */

#endif /* CRYPTO_SCHNORRSIGNATURE_H_ */
