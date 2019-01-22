/*
 * test_conversion.cpp
 *
 *  Created on: 2019/01/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "numeric/Conversion.h"
#include "numeric/BigInteger.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

using namespace alinous;


TEST_GROUP(TestConversionGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestConversionGroup, classval){
	StackMultipleRelease<UnicodeString> rel;
	BigInteger zero(0, 0);

	UnicodeString* str0 = Conversion::toDecimalScaledString(zero, 0); rel.add(str0);
	UnicodeString* str = Conversion::toDecimalScaledString(zero, 1); rel.add(str);
	UnicodeString* str2 = Conversion::toDecimalScaledString(zero, 2); rel.add(str2);
	UnicodeString* str3 = Conversion::toDecimalScaledString(zero, 3); rel.add(str3);
	UnicodeString* str4 = Conversion::toDecimalScaledString(zero, 4); rel.add(str4);
	UnicodeString* str5 = Conversion::toDecimalScaledString(zero, 5); rel.add(str5);
	UnicodeString* str6 = Conversion::toDecimalScaledString(zero, 6); rel.add(str6);
	UnicodeString* str7 = Conversion::toDecimalScaledString(zero, 7); rel.add(str7);

	UnicodeString* str8 = Conversion::toDecimalScaledString(zero, -1); rel.add(str8);

	UnicodeString ans0(L"0");
	UnicodeString ans1(L"0.0");
	UnicodeString ans2(L"0.00");
	UnicodeString ans3(L"0.000");
	UnicodeString ans4(L"0.0000");
	UnicodeString ans5(L"0.00000");
	UnicodeString ans6(L"0.000000");

	CHECK(ans0.equals(str0))
	CHECK(ans1.equals(str))
	CHECK(ans2.equals(str2))
	CHECK(ans3.equals(str3))
	CHECK(ans4.equals(str4))
	CHECK(ans5.equals(str5))
	CHECK(ans6.equals(str6))
}

TEST(TestConversionGroup, classval2){
	StackMultipleRelease<UnicodeString> rel;
	UnicodeString str(L"10");
	BigInteger big(&str, 10);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, -10); rel.add(str0);
	UnicodeString ans(L"1.0E+11");
	CHECK(ans.equals(str0))
}

TEST(TestConversionGroup, classval3){
	StackMultipleRelease<UnicodeString> rel;
	UnicodeString str(L"10");
	BigInteger big(&str, 10);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, 1); rel.add(str0);
	UnicodeString ans(L"1.0");
	CHECK(ans.equals(str0))
}

TEST(TestConversionGroup, classval4){
	StackMultipleRelease<UnicodeString> rel;
	UnicodeString str(L"-10");
	BigInteger big(&str, 10);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, 1); rel.add(str0);
	UnicodeString ans(L"-1.0");
	CHECK(ans.equals(str0))
}

TEST(TestConversionGroup, classval5){
	StackMultipleRelease<UnicodeString> rel;
	UnicodeString str(L"-878824397432651481891353247987891423768534321387864361143548364457698487264387568743568743265873246576467643756437657436587436");
	BigInteger big(&str, 10);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, -100); rel.add(str0);
	UnicodeString ans(L"-8.78824397432651481891353247987891423768534321387864361143548364457698487264387568743568743265873246576467643756437657436587436E+225");
	CHECK(ans.equals(str0))
}

TEST(TestConversionGroup, classval6){
	StackMultipleRelease<UnicodeString> rel;
	UnicodeString str(L"FF");
	BigInteger big(&str, 16);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, -4); rel.add(str0);
	UnicodeString ans(L"2.55E+6");
	CHECK(ans.equals(str0))
}

TEST(TestConversionGroup, classval7){
	StackMultipleRelease<UnicodeString> rel;
	UnicodeString str(L"FFFFFFFF");
	BigInteger big(&str, 16);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, 1); rel.add(str0);
	UnicodeString ans(L"429496729.5");
	CHECK(ans.equals(str0))
}

TEST(TestConversionGroup, classval8){
	StackMultipleRelease<UnicodeString> rel;
	UnicodeString str(L"-100");
	BigInteger big(&str, 16);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, 8); rel.add(str0);
	UnicodeString ans(L"-0.00000256");
	CHECK(ans.equals(str0))
}

TEST(TestConversionGroup, classval9){
	StackMultipleRelease<UnicodeString> rel;
	UnicodeString str(L"1");
	BigInteger big(&str, 10);

	UnicodeString* str0 = Conversion::toDecimalScaledString(big, -16); rel.add(str0);
	UnicodeString ans(L"1E+16");
	CHECK(ans.equals(str0))
}

TEST(TestConversionGroup, divideLongByBillion){
	int64_t v = -0xFFFFFFFFF;
	int64_t a = Conversion::divideLongByBillion(v);

	CHECK(a == 4252339235752966596)
}
