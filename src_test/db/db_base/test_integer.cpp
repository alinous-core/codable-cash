/*
 * test_integer.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/Integer.h"
#include "base/UnicodeString.h"
#include "base/exceptions.h"

using namespace alinous;

TEST_GROUP(IntegerTestGroup) {
	friend class Integer;
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(IntegerTestGroup, construct){
	Integer* value = new Integer(100);
	const Integer cpy(*value);
	Integer cpy2(cpy);
	Integer cpy3(0);

	cpy3 = cpy;
	CHECK(cpy3.value == 100);

	//Integer* cpy2 = new Integer(cpy);
	delete value;
	//delete cpy2;
}

TEST(IntegerTestGroup, parseInt){
	UnicodeString str100(L"100");
	UnicodeString strm100(L"-100");


	int value = Integer::parseInt(&str100);
	CHECK(value == 100);

	value = Integer::parseInt(&strm100);
	CHECK(value == -100);
}

void test_error(UnicodeString* str, int radix){
	int value;
	NumberFormatException* exp = nullptr;
	try{
		value = Integer::parseInt(str, radix);
	}
	catch(NumberFormatException* e){
		exp = e;
	}
	if(exp == nullptr){throw -1;} delete exp;
}

TEST(IntegerTestGroup, parseIntError){
	UnicodeString strerror(L"rtyds");
	UnicodeString strerror2(L"1224T");
	UnicodeString strerror3(L"9999999999999999999999999999999999999999999999999999999999999999");
	UnicodeString strerror4(L"-");
	UnicodeString strerror_null(L"");


	test_error(&strerror, 10);
	test_error(&strerror2, 10);
	test_error(&strerror3, 10);
	test_error(&strerror4, 10);
	test_error(&strerror_null, 10);
}

TEST(IntegerTestGroup, parseIntError16){
	UnicodeString strerror(L"rtyds");
	UnicodeString strerror2(L"1224T");
	UnicodeString strerror3(L"9999999999999999999999999999999999999999999999999999999999999999");
	UnicodeString strerror4(L"-");
	UnicodeString strerror_null(L"");

	test_error(&strerror, 16);
	test_error(&strerror2, 16);
	test_error(&strerror3, 16);
	test_error(&strerror4, 16);
	test_error(&strerror_null, 16);
}

class TInteger : public Integer {
public:
	static void test_error2(UnicodeString* str, int offset, int radix, bool negative){
		int value;
		NumberFormatException* exp = nullptr;
		try{
			value = Integer::parse(str, offset, radix, negative);
		}
		catch(NumberFormatException* e){
			exp = e;
		}
		if(exp == nullptr){ throw -1;}
		delete exp;
	}
};

TEST(IntegerTestGroup, parseIntError2){
	UnicodeString strerror(L"-124");

	TInteger::test_error2(&strerror, 0, 10, false);
	TInteger::test_error2(&strerror, 0, 10, true);
}

TEST(IntegerTestGroup, parseIntError2_strerror2){
	UnicodeString strerror2(L"-1A24");

	TInteger::test_error2(&strerror2, 0, 10, true);
	TInteger::test_error2(&strerror2, 0, 10, false);
}

TEST(IntegerTestGroup, parseIntError2_strerror3){
	UnicodeString strerror3(L"FFFFFFFFFFFFFFFF");

	TInteger::test_error2(&strerror3, 0, 16, false);
	TInteger::test_error2(&strerror3, 0, 10, true);
}

TEST(IntegerTestGroup, parseIntError2_strerror4){
	UnicodeString strerror4(L"-FFFFFFFFFFFFFFFF");

	TInteger::test_error2(&strerror4, 0, 16, false);
	TInteger::test_error2(&strerror4, 0, 10, true);
}

TEST(IntegerTestGroup, parseIntError2_strerror5){
	//UnicodeString strerror5(L"2147483648");
	UnicodeString strerror5(L"2147483649");

	//TInteger::test_error2(&strerror5, 0, 10, true);
	TInteger::test_error2(&strerror5, 0, 10, false);
}

TEST(IntegerTestGroup, parseIntError2_strerror6){
	UnicodeString strerror6(L"1119");

	TInteger::test_error2(&strerror6, 0, -10, false);
}

TEST(IntegerTestGroup, parseIntRaxixError){
	UnicodeString str100(L"100");


	NumberFormatException* exp = nullptr;
	int value;
	try{
		value = Integer::parseInt(&str100, 100);
	}
	catch(NumberFormatException* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;
}

TEST(IntegerTestGroup, toString){
	UnicodeString* str = Integer::toString(-100, 100);
	UnicodeString ans(L"-100");

	CHECK(ans.equals(str))

	delete str;
}

TEST(IntegerTestGroup, toString02){
	UnicodeString* str = Integer::toString(0, 10);
	UnicodeString ans(L"0");

	CHECK(ans.equals(str))

	delete str;
}

TEST(IntegerTestGroup, toString03){
	UnicodeString* str = Integer::toString(0xFFFF, 16);
	UnicodeString ans(L"ffff");

	CHECK(ans.equals(str))

	delete str;
}
