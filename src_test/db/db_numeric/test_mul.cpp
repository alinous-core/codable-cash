/*
 * test_mul.cpp
 *
 *  Created on: 2019/01/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "numeric/BigInteger.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "base_io/ByteBuffer.h"

using namespace alinous;

TEST_GROUP(TestBigIntegerMulGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestBigIntegerMulGroup, mul01){
	StackMultipleRelease<UnicodeString> rel;
	BigInteger big1(100);
	BigInteger big2(200);

	BigInteger big = big1.multiply(big2);

	UnicodeString str0 = big.toString();
	UnicodeString ans(L"20000");
	CHECK(ans.equals(str0))
}

TEST(TestBigIntegerMulGroup, mul02){
	StackMultipleRelease<UnicodeString> rel;

	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"100");
	BigInteger big1(&bstr1, 10);
	BigInteger big2(&bstr2, 10);

	BigInteger big = big1.multiply(big2);

	UnicodeString str0 = big.toString();
	UnicodeString ans(L"1000");
	CHECK(ans.equals(str0))
}

TEST(TestBigIntegerMulGroup, mul03){
	StackMultipleRelease<UnicodeString> rel;

	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"-100");
	BigInteger big1(&bstr1, 10);
	BigInteger big2(&bstr2, 10);

	BigInteger big = big1.multiply(big2);

	UnicodeString str0 = big.toString();
	UnicodeString ans(L"-1000");
	CHECK(ans.equals(str0))
}

TEST(TestBigIntegerMulGroup, mul04){
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

TEST(TestBigIntegerMulGroup, mul05){
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

TEST(TestBigIntegerMulGroup, mul06){
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

TEST(TestBigIntegerMulGroup, mul06_1){
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

TEST(TestBigIntegerMulGroup, mul06_2){
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


TEST(TestBigIntegerMulGroup, mul06_3){
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

TEST(TestBigIntegerMulGroup, mul06_4){
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

TEST(TestBigIntegerMulGroup, mul06_5){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"0");
	UnicodeString bstr(L"0");

	BigInteger big1(&bstr1, radix);
	BigInteger big2 = BigInteger::valueOf(-1);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}


TEST(TestBigIntegerMulGroup, mul07){
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

TEST(TestBigIntegerMulGroup, mul08){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"10");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	big1 = big1.pow(0).multiply(big1.pow(600)).pow(1);
	big2 = big2.pow(700);
	ans = ans.pow(1300);

	BigInteger big = big1.multiply(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(TestBigIntegerMulGroup, mul09){
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

