/*
 * IKeyPair.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef CRYPTO_IKEYPAIR_H_
#define CRYPTO_IKEYPAIR_H_

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class IKeyPair {
public:
	virtual ~IKeyPair();

	virtual IKeyPair* clone() const noexcept = 0;
	virtual ByteBuffer* toBinary() const = 0;
};

} /* namespace codablecash */

#endif /* CRYPTO_IKEYPAIR_H_ */
