/*
 * test_unicode_string.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"

#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(UnicodeStringTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(UnicodeStringTestGroup, destruct){
	const wchar_t* str = L"Hello";
	UnicodeString *ptr = new UnicodeString(str);
	delete ptr;
}

TEST(UnicodeStringTestGroup, test01){
	const wchar_t* str = L"Hello";
	UnicodeString ustr(str);

	CHECK(ustr.length() == 5);
	CHECK(!ustr.isEmpty())

	wchar_t ch = ustr.get(0);
	CHECK(ch == 'H');
	ch = ustr.charAt(1);
	CHECK(ch == 'e');
}

TEST(UnicodeStringTestGroup, hash){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"Hello");
	UnicodeString str03(L"HelloWorld");
	UnicodeString str04(L"");


	CHECK(str01.hashCode() == str02.hashCode());
	CHECK(str01.hashCode() != str03.hashCode());
	CHECK(str04.hashCode() == 0);
}

TEST(UnicodeStringTestGroup, equals){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"Hello");
	UnicodeString str03(L"HelloWorld");

	CHECK(str01.equals(&str02));
	CHECK(!str01.equals(&str03));
}

TEST(UnicodeStringTestGroup, __equals){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"Hello");
	UnicodeString str03(L"HelloWorld");
	UnicodeString str04(L"HelloWorlD");

	CHECK(str01.__equals(&str02));
	CHECK(!str01.__equals(&str03));
	CHECK(!str03.__equals(&str04));
}

TEST(UnicodeStringTestGroup, buffer){
	UnicodeString str01(L"Hello");
	UnicodeString str(L"", 2);

	str.append(L'H')->append(L'e');

	str.append(L'l');
	str.append(L'l');
	str.append(L'o');

	CHECK(str01.equals(&str));
}

TEST(UnicodeStringTestGroup, buffer2){
	UnicodeString str01(L"Hello", 2);
	UnicodeString str02(L"Hello", 2);
	UnicodeString str03(L"HelloWorld", 2);
	UnicodeString str04(L"HelloWorlD", 2);

	CHECK(str01.__equals(&str02));
	CHECK(!str01.__equals(&str03));
	CHECK(!str03.__equals(&str04));
}

TEST(UnicodeStringTestGroup, buffer3){
	UnicodeString str01(L"Hello", 2);
	UnicodeString str02(L"Hello", 2);
	UnicodeString str03(L"HelloWorld", 2);
	UnicodeString str04(L"HelloWorlD", 2);

	CHECK(str01.equals(&str02));
	CHECK(!str01.equals(&str03));
	CHECK(!str03.equals(&str04));
}
