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

#include "numeric/BigInteger.h"

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class SchnorrConsts {
public:
	const BigInteger Q;
	const BigInteger Q_1;
	const BigInteger G;

	SchnorrConsts();
	~SchnorrConsts();
};


class Schnorr {
public:
	static constexpr int keyLength = 256;
	static SchnorrConsts cnsts;

	static SchnorrKeyPair* generateKey();
	static SchnorrSignature* sign(const BigInteger& s, const BigInteger& p, const uint8_t* data, size_t size);
	static bool verify(const BigInteger& e, const BigInteger& y, const BigInteger& p, const uint8_t* data, size_t size);
	static bool verify(const SchnorrSignature& sig, const BigInteger& p, const uint8_t* data, size_t size);

	Schnorr();
	virtual ~Schnorr();

	static ByteBuffer* toByteBuffer(const BigInteger& s) noexcept;

};

}

#endif /* CRYPTO_SCHNORR_H_ */
