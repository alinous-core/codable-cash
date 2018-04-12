/*
 * SchnorrKeyPair.h
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#ifndef CRYPTO_SCHNORRKEYPAIR_H_
#define CRYPTO_SCHNORRKEYPAIR_H_

#include <gmp.h>

namespace codablecash {

class SchnorrKeyPair {
public:
	SchnorrKeyPair(mpz_t secretKey, mpz_t publicKey);
	virtual ~SchnorrKeyPair();

	mpz_t secretKey;
	mpz_t publicKey;
};

} /* namespace codablecash */

#endif /* CRYPTO_SCHNORRKEYPAIR_H_ */
