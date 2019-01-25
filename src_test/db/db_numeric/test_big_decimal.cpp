/*
 * test_big_decimal.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */



#include "test_utils/t_macros.h"

#include "numeric/BigDecimal.h"
#include "numeric/exceptions.h"
#include "numeric/BigInteger.h"

#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(TestBigDecimalGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestBigDecimalGroup, testException){
	testException<ArithmeticException>();
}


TEST(TestBigDecimalGroup, construct01_0){
	UnicodeString str(L"00.00e+10");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == 0)
}

TEST(TestBigDecimalGroup, construct01){
	{
		UnicodeString str(L"00.00");
		BigDecimal dec(&str);

		int64_t l = dec.longValue();
		CHECK(l == 0)
	}
	{
		UnicodeString str(L"00.00e+10");
		BigDecimal dec(&str);

		int64_t l = dec.longValue();
		CHECK(l == 0)
	}
	{
		UnicodeString str(L"1234567890");
		BigDecimal dec(&str);

		int64_t l = dec.longValue();
		CHECK(l == 1234567890L)
	}
	{
		UnicodeString str(L"1");
		BigDecimal dec(&str);

		int64_t l = dec.longValue();
		CHECK(l == 1)
	}
	{
		UnicodeString str(L"8");
		BigDecimal dec(&str);

		int64_t l = dec.longValue();
		CHECK(l == 8)
	}
	{
		UnicodeString str(L"0");
		BigDecimal dec(&str);

		int64_t l = dec.longValue();
		CHECK(l == 0)
	}
	{
		UnicodeString str(L"00016");
		BigDecimal dec(&str);

		int64_t l = dec.longValue();
		CHECK(l == 16)
	}
}

TEST(TestBigDecimalGroup, construct02){
	UnicodeString str(L"+1234567890");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == 1234567890L)
}

TEST(TestBigDecimalGroup, construct03){
	UnicodeString str(L"-1234567890");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == -1234567890L)
}

TEST(TestBigDecimalGroup, construct04){
	UnicodeString str(L"0.1234567890");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == 0L)
}

TEST(TestBigDecimalGroup, construct05){
	UnicodeString str(L"5.1234567897654321e138");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == 0L)
}

TEST(TestBigDecimalGroup, construct06){
	UnicodeString str(L"123E04");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == 1230000L)
}

TEST(TestBigDecimalGroup, construct07){
	UnicodeString str(L"-1.234E-112");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	CHECK(l == 0)
}

TEST(TestBigDecimalGroup, construct08){
	UnicodeString str(L"3132342342341908309182309128393331323423423419083091823091283933");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	//CHECK(l == 0)

}

TEST(TestBigDecimalGroup, construct09){
	UnicodeString str(L"31323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	//CHECK(l == 0)

}

TEST(TestBigDecimalGroup, construct10){
	UnicodeString str(L"1234567890123456789");
	BigDecimal dec(&str);

	int64_t l = dec.longValue();
	//CHECK(l == 0)

}

TEST(TestBigDecimalGroup, construct11){
	UnicodeString str(L"3132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933313234234234190830918230912839333132342342341908309182309128393331323423423419083091823091283933");
	BigDecimal dec(&str);

	BigInteger big = dec.toBigInteger();
	UnicodeString ans = big.toString(10);
	CHECK(ans.equals(str))
}

