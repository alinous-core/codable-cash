/*
 * Schnorr.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "Schnorr.h"

#include "osenv/memory.h"
#include "yescrypt/sha256.h"
#include "base_io/ReverseByteBuffer.h"
#include "base/StackRelease.h"

namespace codablecash {



SchnorrConsts::SchnorrConsts(){
	mpz_init_set_str(this->Q, "ff66c4652cbb54e13e4cc75898014aef72332e147343a95031cf416ca9f77ce7", 16);
	mpz_init_set_str(this->Q_1, "ff66c4652cbb54e13e4cc75898014aef72332e147343a95031cf416ca9f77ce6", 16);
	mpz_init_set_str(this->G, "e000000000000000000000000000000000000000000000000000000000000002", 16);
}
SchnorrConsts::~SchnorrConsts(){
	mpz_clear(this->Q);
	mpz_clear(this->Q_1);
	mpz_clear(this->G);
}

SchnorrConsts Schnorr::cnsts;

Schnorr::Schnorr() {
}

Schnorr::~Schnorr() {
}

SchnorrKeyPair* Schnorr::generateKey(){
	mpz_t s, p;
	mpz_init(s);
	mpz_init(p);

	gmp_randstate_t state;
	gmp_randinit_default(state);

	mpz_urandomb (s, state, 256);

	mpz_powm(p, cnsts.G, s, cnsts.Q);

	SchnorrKeyPair* pair = new SchnorrKeyPair(s, p);

	gmp_randclear(state);
	mpz_clear(s);
	mpz_clear(p);

	return pair;
}

SchnorrSignature* Schnorr::sign(const mpz_t s, const mpz_t p, const uint8_t* data, size_t size){
	mpz_t e, y;
	mpz_init(e);
	mpz_init(y);


	mpz_t r, powG;
	mpz_init(r);
	{
		gmp_randstate_t state;
		gmp_randinit_default(state);
		mpz_urandomb (r, state, 256);
		gmp_randclear(state);
	}

	mpz_init(powG);
	mpz_powm(powG, cnsts.G, r, cnsts.Q);

	{
		size_t count;
		uint8_t* buff =  (uint8_t*)mpz_export(NULL, &count, 1, 1, 1, 0, powG);

		size_t hashinLen = count + size;
		uint8_t* hashin = new uint8_t[hashinLen];
		alinous::Mem::memcpy(hashin, data, size);
		alinous::Mem::memcpy(hashin + size, buff, count);

		SHA256_CTX ctx;
		SHA256_Init(&ctx);
		SHA256_Update(&ctx, hashin, hashinLen);

		uint8_t sha256[32];
		SHA256_Final((uint8_t *)sha256, &ctx);

		mpz_import(e, 32, 1, 1, 1, 0, sha256);

		delete [] hashin;
		free(buff);
	}

	mpz_mul(powG, s, e);
	mpz_sub(y, r, powG);
	mpz_mod(y, y, cnsts.Q_1);

	SchnorrSignature* sig = new SchnorrSignature(e, y);

	mpz_clear(r);
	mpz_clear(powG);
	mpz_clear(e);
	mpz_clear(y);


	return sig;
}

bool Schnorr::verify(const SchnorrSignature* sig, const mpz_t p, const uint8_t* data, size_t size){
	return verify(sig->e, sig->y, p, data, size);
}

bool Schnorr::verify(const mpz_t e, const mpz_t y, const mpz_t p, const uint8_t* data, size_t size){
	mpz_t eP, yG, powG, e2;
	mpz_init(eP);
	mpz_init(yG);
	mpz_init(powG);
	mpz_init(e2);

	mpz_powm(eP, p, e, cnsts.Q);
	mpz_powm(yG, cnsts.G, y, cnsts.Q);

	mpz_mul(powG, eP, yG);
	mpz_mod(powG, powG, cnsts.Q);

	{
		size_t count;
		uint8_t* buff =  (uint8_t*)mpz_export(NULL, &count, 1, 1, 1, 0, powG);

		size_t hashinLen = count + size;
		uint8_t* hashin = new uint8_t[hashinLen];
		alinous::Mem::memcpy(hashin, data, size);
		alinous::Mem::memcpy(hashin + size, buff, count);

		SHA256_CTX ctx;
		SHA256_Init(&ctx);
		SHA256_Update(&ctx, hashin, hashinLen);

		uint8_t sha256[32];
		SHA256_Final((uint8_t *)sha256, &ctx);

		mpz_import(e2, 32, 1, 1, 1, 0, sha256);

		delete [] hashin;
		free(buff);
	}

	int cmp = mpz_cmp(e, e2);

	mpz_clear(eP);
	mpz_clear(yG);
	mpz_clear(powG);
	mpz_clear(e2);

	return cmp == 0;
}

ByteBuffer* Schnorr::toByteBuffer(const mpz_t s) noexcept {
	size_t count;
	uint8_t* buff =  (uint8_t*)mpz_export(NULL, &count, 1, 1, 1, 0, s);
	StackArrayRelease<uint8_t> __st_buff(buff);

	return ByteBuffer::wrapWithEndian(buff, count, true);
}

}


