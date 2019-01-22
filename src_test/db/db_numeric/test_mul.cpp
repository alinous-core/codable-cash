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
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(BigIntegerMulGroup, mul05){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"100000000000000000000000000000000000000");
	UnicodeString bstr2(L"10000000000000000000000000000000000000000000000");
	UnicodeString bstr(L"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(BigIntegerMulGroup, mul06){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"10");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	big1 = big1.pow(100);
	big2 = big2.pow(80);
	ans = ans.pow(180);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(BigIntegerMulGroup, mul06_1){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"0");
	UnicodeString bstr2(L"0");
	UnicodeString bstr(L"0");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	ans = ans.pow(180);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(BigIntegerMulGroup, mul06_2){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"1");
	UnicodeString bstr2(L"2");
	UnicodeString bstr(L"2");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}


TEST(BigIntegerMulGroup, mul06_3){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"1");
	UnicodeString bstr2(L"1");
	UnicodeString bstr(L"1");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(BigIntegerMulGroup, mul06_4){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"0");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"0");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(BigIntegerMulGroup, mul06_5){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"0");
	UnicodeString bstr(L"0");

	BigInteger big1(&bstr1, radix);
	BigInteger big2 = BigInteger::valueOf(-1);
	BigInteger ans(&bstr, radix);

	int f = big1.getFirstNonzeroDigit();
	CHECK(f == -1)

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}


TEST(BigIntegerMulGroup, mul07){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"10");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	big1 = big1.pow(200);
	big2 = big2.pow(280);
	ans = ans.pow(480);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(BigIntegerMulGroup, mul08){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"10");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	big1 = big1.pow(0).multiply(big1.pow(600)).pow(1);
	big2 = big2.pow(700).shiftRight(0);
	ans = ans.pow(1300);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(BigIntegerMulGroup, mul09){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"-10");
	UnicodeString bstr(L"-10");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	big1 = big1.pow(1000);
	big2 = big2.pow(1001);
	ans = ans.pow(2001);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}
