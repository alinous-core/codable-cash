/*
 * SchnorrSignature.h
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#ifndef CRYPTO_SCHNORRSIGNATURE_H_
#define CRYPTO_SCHNORRSIGNATURE_H_

#include <gmp.h>

namespace alinous {
class BigInteger;
}

namespace codablecash {
using namespace alinous;

class SchnorrSignature {
public:
	BigInteger* e, *y;

	SchnorrSignature(const SchnorrSignature& inst) = delete;
	SchnorrSignature(const BigInteger& e, const BigInteger& y);
	virtual ~SchnorrSignature();
};

} /* namespace codablecash */

#endif /* CRYPTO_SCHNORRSIGNATURE_H_ */
