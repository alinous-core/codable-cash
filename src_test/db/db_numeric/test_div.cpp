/*
 * test_div.cpp
 *
 *  Created on: 2019/01/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "numeric/BigInteger.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

using namespace alinous;

TEST_GROUP(TestBigIntegerDivGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestBigIntegerDivGroup, div01){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"100000000000000000000000");
	UnicodeString bstr2(L"100000000000000000000000");
	UnicodeString bstr(L"1");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.divide(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(TestBigIntegerDivGroup, div02){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"100000000000000000000000");
	UnicodeString bstr2(L"10000");
	UnicodeString bstr(L"10000000000000000000");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.divide(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(TestBigIntegerDivGroup, div03){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10000000000000100000000000000");
	UnicodeString bstr2(L"1");
	UnicodeString bstr(L"10000000000000100000000000000");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.divide(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(TestBigIntegerDivGroup, div04){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10000000000000100000000000000");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"1000000000000010000000000000");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.divide(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(TestBigIntegerDivGroup, div05){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"1000000000000000000");
	UnicodeString bstr2(L"10000000000000100000000000000");
	UnicodeString bstr(L"0");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	BigInteger big = big1.divide(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(TestBigIntegerDivGroup, div06){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"10");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	big1 = big1.pow(10);
	big2 = big2.pow(2);
	ans = ans.pow(8);

	BigInteger big = big1.divide(big2);

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(TestBigIntegerDivGroup, div07){
	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"10");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	big1 = big1.pow(120);
	big2 = big2.pow(100);
	ans = ans.pow(20);

	BigInteger big = big1.divide(big2);

	//UnicodeString* str0 = big.toString(); StackRelease<UnicodeString> __st_str0(str0);
	//::printf("%s\n", str0->toCString());

	bool blans = ans.equals(&big);
	CHECK(blans)
}

TEST(TestBigIntegerDivGroup, div08){

	int32_t sval = 0xffffffff;
	uint32_t uval = 0xffffffff;
	sval = ((uint32_t)sval) >> 8;
	uval >>= 8;

	int si = sizeof(int64_t);

	StackMultipleRelease<UnicodeString> rel;

	int radix = 10;
	UnicodeString bstr1(L"10");
	UnicodeString bstr2(L"10");
	UnicodeString bstr(L"10");

	BigInteger big1(&bstr1, radix);
	BigInteger big2(&bstr2, radix);
	BigInteger ans(&bstr, radix);

	big1 = big1.pow(120);
	big2 = big2.pow(20);
	ans = ans.pow(100);

	BigInteger big = big1.divide(big2);

	//UnicodeString* str0 = big.toString(); StackRelease<UnicodeString> __st_str0(str0);
	//::printf("%s\n", str0->toCString());

	bool blans = ans.equals(&big);
	CHECK(blans)
}

