/*
 * test_schnorr.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include <iostream>
#include <string.h>
#include "CppUTest/CommandLineTestRunner.h"
#include <gmp.h>

#include "crypto/Schnorr.h"

using namespace codablecash;

TEST_GROUP(SchnorrTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(SchnorrTestGroup, test01){
	Schnorr *psc = new Schnorr();

	delete psc;
}

TEST(SchnorrTestGroup, generateKey){
	SchnorrKeyPair* key = Schnorr::generateKey();

	mpz_t ans; mpz_init(ans);

	mpz_powm(ans, Schnorr::cnsts.G, key->secretKey, Schnorr::cnsts.Q);

	CHECK_TRUE(mpz_cmp(ans, key->publicKey) == 0);

	mpz_clear(ans);
	delete key;
}

TEST(SchnorrTestGroup, sign){
	SchnorrKeyPair* key = Schnorr::generateKey();
	const char* testData = "asdfghjjklqwertyuiopzxcvbnm,./poiiuuuytrtrree";
	int size = strlen(testData);

	SchnorrSignature* sig = Schnorr::sign(key->secretKey, key->publicKey, (const uint8_t*)testData, (size_t)size);

	delete key;
	delete sig;
}


