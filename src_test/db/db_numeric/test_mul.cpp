/*
 * test_mul.cpp
 *
 *  Created on: 2019/01/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "numeric/BigInteger.h"
#include "numeric/Conversion.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

using namespace alinous;

TEST_GROUP(BigIntegerMulGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(BigIntegerMulGroup, mul01){
	StackMultipleRelease<UnicodeString> rel;
	BigInteger big1(1, 100);
	BigInteger big2(1, 200);

	BigInteger big = big1.multiply(big2);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, 0); rel.add(str0);
	UnicodeString ans(L"20000");
	CHECK(ans.equals(str0))
}

TEST(BigIntegerMulGroup, mul02){
	StackMultipleRelease<UnicodeString> rel;

	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"100");
	BigInteger big1(&bstr1, 10);
	BigInteger big2(&bstr2, 10);

	BigInteger big = big1.multiply(big2);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, 0); rel.add(str0);
	UnicodeString ans(L"1000");
	CHECK(ans.equals(str0))
}

TEST(BigIntegerMulGroup, mul03){
	StackMultipleRelease<UnicodeString> rel;

	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"-100");
	BigInteger big1(&bstr1, 10);
	BigInteger big2(&bstr2, 10);

	BigInteger big = big1.multiply(big2);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, 0); rel.add(str0);
	UnicodeString ans(L"-1000");
	CHECK(ans.equals(str0))
}

TEST(BigIntegerMulGroup, mul04){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10000000000000000000");
	UnicodeString bstr2(L"100000000000000000000000");
	UnicodeString bstr(L"1000000000000000000000000000000000000000000");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);

	BigInteger big = big1.multiply(big2);

	BigInteger ans(&bstr, radix);

	bool blans = ans.equals(&big);

	CHECK(blans)
}
