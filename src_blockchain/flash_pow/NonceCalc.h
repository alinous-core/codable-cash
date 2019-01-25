/*
 * NanceCalc.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_POW_NONCECALC_H_
#define FLASH_POW_NONCECALC_H_

#include <cstddef>
#include <cstdint>

namespace alinous {
class ByteBuffer;
class BigInteger;
}

namespace codablecash {
using namespace alinous;

class NonceCalc {
public:
	NonceCalc();
	virtual ~NonceCalc();

	ByteBuffer* calc(const ByteBuffer* in, const ByteBuffer* nonce);

	BigInteger calcNecessaryDifficulty(const BigInteger& hashrate, uint64_t targetTimeSec);
	BigInteger calcHash4Diff(const BigInteger& diff);

private:
	static int yescrypt(const uint8_t *passwd, size_t passwdlen,
            const uint8_t *salt, size_t saltlen,
            uint8_t *buf, size_t buflen);
};

} /* namespace codablecash */

#endif /* FLASH_POW_NONCECALC_H_ */
