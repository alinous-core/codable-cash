/*
 * test_big_decimal.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */



#include "test_utils/t_macros.h"

#include "numeric/BigDecimal.h"
#include "numeric/exceptions.h"

#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(BigDecimalGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(BigDecimalGroup, testException){
	testException<ArithmeticException>();
}

TEST(BigDecimalGroup, construct01){
	UnicodeString str(L"1234567890");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == 1234567890L)
}

TEST(BigDecimalGroup, construct02){
	UnicodeString str(L"+1234567890");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == 1234567890L)
}

TEST(BigDecimalGroup, construct03){
	UnicodeString str(L"-1234567890");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == -1234567890L)
}

