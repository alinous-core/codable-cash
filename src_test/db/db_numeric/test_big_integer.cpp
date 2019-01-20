/*
 * test_big_integer.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "numeric/BigInteger.h"

using namespace alinous;

TEST_GROUP(BigIntegerGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(BigIntegerGroup, construct01){
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
