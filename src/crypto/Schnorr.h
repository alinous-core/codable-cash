/*
 * Schnorr.h
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#ifndef CRYPTO_SCHNORR_H_
#define CRYPTO_SCHNORR_H_

#include "SchnorrKeyPair.h"
#include "SchnorrSignature.h"

#include <stdint.h>
#include <stdlib.h>

namespace codablecash {

class SchnorrConsts {
public:
	mpz_t Q;
	mpz_t Q_1;
	mpz_t G;

	SchnorrConsts();
	~SchnorrConsts();
};


class Schnorr {
public:
	static constexpr int keyLength = 256;
	static SchnorrConsts cnsts;
	static SchnorrKeyPair* generateKey();
	static SchnorrSignature* sign(const mpz_t s, const mpz_t p, const uint8_t* data, size_t size);

	Schnorr();
	virtual ~Schnorr();

};

}

#endif /* CRYPTO_SCHNORR_H_ */
