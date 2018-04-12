/*
 * test_schnorr.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include <iostream>
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

