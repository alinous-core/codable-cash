/*
 * NanceCalc.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "NonceCalc.h"

#include "../../src_db/numeric/BigInteger.h"
#include "base_io/ByteBuffer.h"
#include "yescrypt/yescrypt.h"

#define YESCRYPT_N 2048
#define YESCRYPT_R 8
#define YESCRYPT_P 1
#define YESCRYPT_T 0
#define YESCRYPT_FLAGS (YESCRYPT_RW | YESCRYPT_PWXFORM)


namespace codablecash {

NonceCalc::NonceCalc() {
}

NonceCalc::~NonceCalc() {
}

ByteBuffer* codablecash::NonceCalc::calc(const ByteBuffer* in,	const ByteBuffer* nonce) {
	uint8_t buf[32]{};
	yescrypt(in->array(), in->capacity(), nonce->array(), nonce->capacity(), buf, 32);

	return ByteBuffer::wrap(buf, 256);
}

BigInteger NonceCalc::calcNecessaryDifficulty(const BigInteger& hashrate, uint64_t targetTimeSec) {
	BigInteger tm(targetTimeSec);

	return hashrate.multiply(tm);
}

BigInteger NonceCalc::calcHash4Diff(const BigInteger& diff) {
	// 256 bytes
	BigInteger max(L"1", 16);
	max = max.shiftLeft(256);

	BigInteger hash = max.divide(diff);
	return hash;
}



int NonceCalc::yescrypt(const uint8_t* passwd, size_t passwdlen,
		const uint8_t* salt, size_t saltlen, uint8_t* buf, size_t buflen) {
	static __thread int initialized = 0;
	static __thread yescrypt_shared_t shared;
	static __thread yescrypt_local_t local;
	int retval;
	if (!initialized) {
		yescrypt_init_shared(&shared, NULL, 0,
										 0, 0, 0, YESCRYPT_SHARED_DEFAULTS, 0, NULL, 0);
		yescrypt_init_local(&local);
		initialized = 1;
	}
	retval = yescrypt_kdf(&shared, &local, passwd, passwdlen, salt, saltlen,
						  YESCRYPT_N, YESCRYPT_R, YESCRYPT_P, YESCRYPT_T,
							(yescrypt_flags_t)YESCRYPT_FLAGS, buf, buflen);

	return retval;
}

} /* namespace codablecash */
