/*
 * SchnorrKeyPair.h
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#ifndef CRYPTO_SCHNORRKEYPAIR_H_
#define CRYPTO_SCHNORRKEYPAIR_H_

#include <gmp.h>
#include "IKeyPair.h"

namespace alinous {
class BigInteger;
}

namespace codablecash {
using namespace alinous;

class SchnorrKeyPair : public IKeyPair {
public:

	SchnorrKeyPair(const SchnorrKeyPair& inst) = delete;
	SchnorrKeyPair(const BigInteger& secretKey, const BigInteger& publicKey);
	virtual ~SchnorrKeyPair();

	virtual ByteBuffer* toBinary() const;

	BigInteger* secretKey;
	BigInteger* publicKey;
};

} /* namespace codablecash */

#endif /* CRYPTO_SCHNORRKEYPAIR_H_ */
