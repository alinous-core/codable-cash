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


}

