/*
 * test_big_integer.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */


#include "base_io/ByteBuffer.h"
#include "test_utils/t_macros.h"

#include "numeric/BigInteger.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

using namespace alinous;

TEST_GROUP(TestBigIntegerGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestBigIntegerGroup, negate){
	BigInteger big1(100);
	BigInteger big2 = big1.negate();

	CHECK(big2.longValue() == -100)
}

TEST(TestBigIntegerGroup, classval){
	BigInteger big1(100);
	BigInteger big2(200);

	big2 = big1;

	bool bl = big1.equals(&big2);
	CHECK(bl);
}

TEST(TestBigIntegerGroup, construct01){
	BigInteger* big = new BigInteger(100);

	int64_t v = big->longValue();
	CHECK(v = 100);

	delete big;
}

TEST(TestBigIntegerGroup, construct02){
	BigInteger* big = new BigInteger(-100);

	int64_t v = big->longValue();
	CHECK(v = -100);

	delete big;
}

TEST(TestBigIntegerGroup, construct03){
	UnicodeString str(L"100");

	BigInteger* big = new BigInteger(&str);

	int64_t v = big->longValue();
	CHECK(v == 100);

	delete big;
}

TEST(TestBigIntegerGroup, construct04){
	UnicodeString str(L"-100");

	BigInteger* big = new BigInteger(&str);

	int64_t v = big->longValue();
	CHECK(v == -100);

	delete big;
}

TEST(TestBigIntegerGroup, construct05){
	UnicodeString str(L"0");

	BigInteger* big = new BigInteger(&str);

	int64_t v = big->longValue();
	CHECK(v == 0);

	delete big;
}

TEST(TestBigIntegerGroup, construct06){
	UnicodeString str(L"100");

	BigInteger* big = new BigInteger(&str, 10);

	int64_t v = big->longValue();
	CHECK(v == 100);

	delete big;
}

static bool testToString(UnicodeString* str, int radix) {
	{
		BigInteger* big = new BigInteger(str, radix);

		UnicodeString str2 = big->toString(16);

		BigInteger* big2 = new BigInteger(str2, 16);

		bool eq = big->equals(big2);
		if(!eq){
			return false;
		}

		delete big;
		delete big2;
	}

	{
		BigInteger* big = new BigInteger(str, 10);

		UnicodeString str2 = big->toString(10);

		BigInteger* big2 = new BigInteger(str2, 10);

		bool eq = big->equals(big2);
		if(!eq){
			return false;
		}

		delete big;
		delete big2;
	}

	{
		BigInteger* big = new BigInteger(str, 10);

		UnicodeString str2 = big->toString(12);

		BigInteger* big2 = new BigInteger(str2, 12);

		bool eq = big->equals(big2);
		if(!eq){
			return false;
		}

		delete big;
		delete big2;
	}

	return true;
}

TEST(TestBigIntegerGroup, construct07){
	{
		UnicodeString str(L"878824397432651481891353247987891423768534321387864361143548364457698487264387568743568743265873246576467643756437657436587436");
		bool chk = testToString(&str, 10);
		CHECK(chk)
	}
	{
		UnicodeString str(L"-878824397432651481891353247987891423768534321387864361143548364457698487264387568743568743265873246576467643756437657436587436");
		bool chk = testToString(&str, 10);
		CHECK(chk)
	}
	{
		UnicodeString str(L"0");
		bool chk = testToString(&str, 10);
		CHECK(chk)
	}
	{
		UnicodeString str(L"1");
		bool chk = testToString(&str, 10);
		CHECK(chk)
	}
	{
		UnicodeString str(L"-1");
		bool chk = testToString(&str, 10);
		CHECK(chk)
	}
	{
		UnicodeString str(L"10");
		bool chk = testToString(&str, 10);
		CHECK(chk)
	}
	{
		UnicodeString str(L"-10");
		bool chk = testToString(&str, 10);
		CHECK(chk)
	}
	{
		UnicodeString str(L"-10000000000000000");
		bool chk = testToString(&str, 10);
		CHECK(chk)
	}
}

TEST(TestBigIntegerGroup, testShift01){
	BigInteger ff(L"0xff", 16);
	BigInteger shfted = ff.shiftLeft(8);

	BigInteger ans(L"0xff0", 16);

	CHECK(shfted.equals(&ans))
}

TEST(TestBigIntegerGroup, testShift02){
	BigInteger ff(L"0xff", 16);
	BigInteger shfted = ff.shiftRight(-8);

	BigInteger ans(L"0xff0", 16);

	CHECK(shfted.equals(&ans))
}

TEST(TestBigIntegerGroup, testShift03){
	BigInteger ff(L"0xff", 16);
	BigInteger shfted = ff.shiftRight(8);

	BigInteger ans(L"0xf", 16);

	CHECK(shfted.equals(&ans))
}

TEST(TestBigIntegerGroup, testShift04){
	BigInteger ff(L"0xff", 16);
	BigInteger shfted = ff.shiftLeft(-8);

	BigInteger ans(L"0xf", 16);

	CHECK(shfted.equals(&ans))
}

TEST(TestBigIntegerGroup, testShift05){
	BigInteger ff((int64_t)10);
	BigInteger shfted = ff.shiftLeft(0);
	BigInteger shfted2 = ff.shiftRight(0);

	CHECK(shfted.equals(&ff))
	CHECK(shfted2.equals(&ff))
}

TEST(TestBigIntegerGroup, testabs){
	BigInteger ff((int64_t)-10);
	BigInteger ff2((int64_t)10);

	BigInteger ans = ff.abs();
	CHECK(ff2.equals(&ans))
}

TEST(TestBigIntegerGroup, testadd){
	BigInteger ff((int64_t)-10);
	BigInteger ff2((int64_t)10);
	BigInteger ff3((int64_t)0);

	BigInteger ans = ff.add(ff2);
	CHECK(ans.equals(&ff3))
}

TEST(TestBigIntegerGroup, testsub){
	BigInteger ff((int64_t)10);
	BigInteger ff2((int64_t)10);
	BigInteger ff3((int64_t)0);

	BigInteger ans = ff.subtract(ff2);
	CHECK(ans.equals(&ff3))
}

TEST(TestBigIntegerGroup, testtestbit){
	BigInteger ff((int64_t)8);

	CHECK(ff.testBit(0) == 0);
	CHECK(ff.testBit(1) == 0);
	CHECK(ff.testBit(2) == 0);
	CHECK(ff.testBit(3) == 1);
	CHECK(ff.testBit(4) == 0);
}

TEST(TestBigIntegerGroup, binary){
	UnicodeString bstr1(L"100000000000000000000000000000000000000");
	BigInteger big1(&bstr1, 10);

	ByteBuffer* buff = big1.toBinary();

	BigInteger* ans = BigInteger::fromBinary((const char*)buff->array(), buff->capacity());

	UnicodeString str = ans->toString(10);

	bool bl = bstr1.equals(str);

	delete buff;
	delete ans;
}

TEST(TestBigIntegerGroup, mod){
	BigInteger big1(UnicodeString(L"11"), 10);
	BigInteger big2(UnicodeString(L"100"));

	BigInteger ans = big1.mod(big2);
	bool res = ans.toString().equals(UnicodeString(L"11"));
	CHECK(res)
}


