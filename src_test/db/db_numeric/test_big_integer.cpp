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

TEST(BigIntegerGroup, negate){
	BigInteger big1(100);
	BigInteger big2 = big1.negate();

	CHECK(big2.longValue() == -100)
}

TEST(BigIntegerGroup, classval){
	BigInteger big1(100);
	BigInteger big2(200);

	big2 = big1;

	bool bl = big1.equals(&big2);
	CHECK(bl);
}

TEST(BigIntegerGroup, construct01){
	BigInteger* big = new BigInteger(100);

	int64_t v = big->longValue();
	CHECK(v = 100);

	delete big;
}

TEST(BigIntegerGroup, construct02){
	BigInteger* big = new BigInteger(-100);

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

static bool testToString(UnicodeString* str, int radix) {
	{
		BigInteger* big = new BigInteger(str, radix);

		UnicodeString* str2 = big->toString(16);

		BigInteger* big2 = new BigInteger(str2, 16);

		bool eq = big->equals(big2);
		if(!eq){
			return false;
		}

		delete str2;
		delete big;
		delete big2;
	}

	{
		BigInteger* big = new BigInteger(str, 10);

		UnicodeString* str2 = big->toString(10);

		BigInteger* big2 = new BigInteger(str2, 10);

		bool eq = big->equals(big2);
		if(!eq){
			return false;
		}

		delete str2;
		delete big;
		delete big2;
	}

	{
		BigInteger* big = new BigInteger(str, 10);

		UnicodeString* str2 = big->toString(12);

		BigInteger* big2 = new BigInteger(str2, 12);

		bool eq = big->equals(big2);
		if(!eq){
			return false;
		}

		delete str2;
		delete big;
		delete big2;
	}

	return true;
}

TEST(BigIntegerGroup, construct07){
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

TEST(BigIntegerGroup, testShift01){
	BigInteger ff(L"0xff", 16);
	BigInteger shfted = ff.shiftLeft(8);

	BigInteger ans(L"0xff0", 16);

	CHECK(shfted.equals(&ans))
}

TEST(BigIntegerGroup, testShift02){
	BigInteger ff(L"0xff", 16);
	BigInteger shfted = ff.rightShift(-8);

	BigInteger ans(L"0xff0", 16);

	CHECK(shfted.equals(&ans))
}

TEST(BigIntegerGroup, testShift03){
	BigInteger ff(L"0xff", 16);
	BigInteger shfted = ff.rightShift(8);

	BigInteger ans(L"0xf", 16);

	CHECK(shfted.equals(&ans))
}

TEST(BigIntegerGroup, testShift04){
	BigInteger ff(L"0xff", 16);
	BigInteger shfted = ff.shiftLeft(-8);

	BigInteger ans(L"0xf", 16);

	CHECK(shfted.equals(&ans))
}

TEST(BigIntegerGroup, testShift05){
	BigInteger ff((int64_t)10);
	BigInteger shfted = ff.shiftLeft(0);
	BigInteger shfted2 = ff.rightShift(0);

	CHECK(shfted.equals(&ff))
	CHECK(shfted2.equals(&ff))
}

