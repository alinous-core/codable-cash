/*
 * test_long.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base/Long.h"
#include "base/Exception.h"

using namespace alinous;

TEST_GROUP(LongTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(LongTestGroup, test01){
	Long l;
}

TEST(LongTestGroup, test02){
	UnicodeString* str = Long::toString(123456789012, 16);
	UnicodeString ans(L"1cbe991a14");

	CHECK(str->equals(&ans))
	delete str;
}

TEST(LongTestGroup, test03){
	UnicodeString* str = Long::toString(-123456789012, 16);
	UnicodeString ans(L"-1cbe991a14");

	CHECK(str->equals(&ans))
	delete str;
}

TEST(LongTestGroup, test04){
	UnicodeString* str = Long::toString(-123456789012, 100);
	UnicodeString ans(L"-123456789012");

	CHECK(str->equals(&ans))
	delete str;
}

TEST(LongTestGroup, test05){
	UnicodeString* str = Long::toString(0, 100);
	UnicodeString ans(L"0");

	CHECK(str->equals(&ans))
	delete str;
}

TEST(LongTestGroup, test06){
	UnicodeString str(L"z");

	Exception* ex = nullptr;

	try{
		Long::parse(&str, 0, 16, false);
	}
	catch(Exception* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

