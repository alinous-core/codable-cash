/*
 * test_big_integer.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "numeric/BigInteger.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

using namespace alinous;

TEST_GROUP(BigIntegerGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(BigIntegerGroup, construct01){
	BigInteger::test();

	BigInteger* big = new BigInteger(1, 100);

	int64_t v = big->longValue();
	CHECK(v = 100);

	delete big;
}
TEST(BigIntegerGroup, construct02){
	BigInteger* big = new BigInteger(-1, 100);

	int64_t v = big->longValue();
	CHECK(v = -100);

	delete big;
}

TEST(BigIntegerGroup, construct03){
	UnicodeString str(L"100");

	BigInteger* big = new BigInteger(&str);

	int64_t v = big->longValue();
	CHECK(v == 100);

	delete big;
}

TEST(BigIntegerGroup, construct04){
	UnicodeString str(L"-100");

	BigInteger* big = new BigInteger(&str);

	int64_t v = big->longValue();
	CHECK(v == -100);

	delete big;
}

TEST(BigIntegerGroup, construct05){
	UnicodeString str(L"0");

	BigInteger* big = new BigInteger(&str);

	int64_t v = big->longValue();
	CHECK(v == 0);

	delete big;
}

TEST(BigIntegerGroup, construct06){
	UnicodeString str(L"100");

	BigInteger* big = new BigInteger(&str, 10);

	int64_t v = big->longValue();
	CHECK(v == 100);

	delete big;
}
