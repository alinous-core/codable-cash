/*
 * Schnorr.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "crypto/Schnorr.h"

#include "base_io/ByteBuffer.h"
#include "osenv/memory.h"
#include "yescrypt/sha256.h"
#include "base_io/ReverseByteBuffer.h"
#include "base/StackRelease.h"

namespace codablecash {



SchnorrConsts::SchnorrConsts()
				: Q(L"ff66c4652cbb54e13e4cc75898014aef72332e147343a95031cf416ca9f77ce7", 16),
				  Q_1(L"ff66c4652cbb54e13e4cc75898014aef72332e147343a95031cf416ca9f77ce6", 16),
				  G(L"e000000000000000000000000000000000000000000000000000000000000002", 16)
{
}
SchnorrConsts::~SchnorrConsts(){
}

SchnorrConsts Schnorr::cnsts;

Schnorr::Schnorr() {
}

Schnorr::~Schnorr() {
}

SchnorrKeyPair* Schnorr::generateKey(){
	BigInteger s = BigInteger::ramdom();
	BigInteger p = cnsts.G.modPow(s, cnsts.Q);

	SchnorrKeyPair* pair = new SchnorrKeyPair(s, p);
	return pair;
}

SchnorrSignature* Schnorr::sign(const BigInteger& s, const BigInteger& p, const uint8_t* data, size_t size){
	BigInteger r = BigInteger::ramdom();
	BigInteger powG = cnsts.G.modPow(r, cnsts.Q);

	BigInteger* e = nullptr;
	{
		ByteBuffer* buff = powG.toBinary();
		StackRelease<ByteBuffer> __st_buff(buff);

		int count = buff->capacity();
		size_t hashinLen = count + size;
		uint8_t* hashin = new uint8_t[hashinLen];
		alinous::Mem::memcpy(hashin, data, size);
		alinous::Mem::memcpy(hashin + size, buff->array(), count);

		SHA256_CTX ctx;
		SHA256_Init(&ctx);
		SHA256_Update(&ctx, hashin, hashinLen);

		uint8_t sha256[32];
		SHA256_Final((uint8_t *)sha256, &ctx);

		e = BigInteger::fromBinary((const char*)sha256, 32);

		delete [] hashin;
	}
	StackRelease<BigInteger> __st_e(e);

	powG = s.multiply(*e);
	BigInteger y = r.subtractSelf(powG).modSelf(cnsts.Q_1);

	SchnorrSignature* sig = new SchnorrSignature(*e, y);

	return sig;
}

bool Schnorr::verify(const SchnorrSignature& sig, const BigInteger& p, const uint8_t* data, size_t size){
	return verify(*sig.e, *sig.y, p, data, size);
}

bool Schnorr::verify(const BigInteger& e, const BigInteger& y, const BigInteger& p, const uint8_t* data, size_t size){
	BigInteger eP = p.modPow(e, cnsts.Q);
	BigInteger yG = cnsts.G.modPow(y, cnsts.Q);
	BigInteger powG = eP.multiplySelf(yG).modSelf(cnsts.Q);

	BigInteger* e2 = nullptr;
	{
		ByteBuffer* buff = powG.toBinary();
		StackRelease<ByteBuffer> __st_buff(buff);

		int count = buff->capacity();
		size_t hashinLen = count + size;
		uint8_t* hashin = new uint8_t[hashinLen];
		alinous::Mem::memcpy(hashin, data, size);
		alinous::Mem::memcpy(hashin + size, buff->array(), count);

		SHA256_CTX ctx;
		SHA256_Init(&ctx);
		SHA256_Update(&ctx, hashin, hashinLen);

		uint8_t sha256[32];
		SHA256_Final((uint8_t *)sha256, &ctx);

		e2 = BigInteger::fromBinary((const char*)sha256, 32);

		delete [] hashin;
	}
	StackRelease<BigInteger> __st_e2(e2);

	int cmp = e.compareTo(*e2);

	return cmp == 0;
}

ByteBuffer* Schnorr::toByteBuffer(const BigInteger& s) noexcept {
	return s.toBinary();
}

}


