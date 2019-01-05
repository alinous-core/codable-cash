/*
 * Sha256.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef CRYPTO_SHA256_H_
#define CRYPTO_SHA256_H_

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class Sha256 {
public:
	static ByteBuffer* sha256(const char* binary, int length, bool bigEndian) noexcept;

};

} /* namespace codablecash */

#endif /* CRYPTO_SHA256_H_ */
