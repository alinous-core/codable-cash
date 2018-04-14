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

TEST(UnicodeStringTestGroup, startsWith){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"He");
	UnicodeString str03(L"el");
	UnicodeString str04(L"Hello2");

	CHECK(str01.startsWith(&str02));
	CHECK(!str01.startsWith(&str03));

	CHECK(str01.startsWith(&str01));
	CHECK(!str01.startsWith(&str04));
}

TEST(UnicodeStringTestGroup, endsWith){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"llo");
	UnicodeString str03(L"el");
	UnicodeString str04(L"2Hello");

	CHECK(str01.endsWith(&str02));
	CHECK(!str01.endsWith(&str04));
}

TEST(UnicodeStringTestGroup, substring){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"ello");

	UnicodeString *str = str01.substring(1);
	CHECK(str->equals(&str02));
	delete str;
}

TEST(UnicodeStringTestGroup, upper_lower){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"HELLO");
	UnicodeString str03(L"hello");

	UnicodeString *str = str01.toLowerCase();
	CHECK(str->equals(&str03));
	delete str;

	str = str01.toUpperCase();
	CHECK(str->equals(&str02));
	delete str;
}

TEST(UnicodeStringTestGroup, indexOf){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"llo");
	UnicodeString str03(L"llo1");
	UnicodeString str04(L"2Hello");
	UnicodeString str05(L"o123");
	UnicodeString str06(L"o123Hello");
	UnicodeString str07(L"ell1");
	UnicodeString str08(L"Hi");

	CHECK(str01.indexOf(&str02) == 2);
	CHECK(str01.indexOf(&str04) < 1);
	CHECK(str01.indexOf(&str03) < 1);
	CHECK(str01.indexOf(&str05) < 1);

	CHECK(str01.indexOf(L'e') == 1);
	CHECK(str01.indexOf(L'T') < 1);

	CHECK(str01.lastIndexOf(&str02) == 2);
	CHECK(str01.lastIndexOf(L'l') == 3);
	CHECK(str01.lastIndexOf(L'T') < 0);
	CHECK(str01.lastIndexOf(&str02, 100) == 2);
	CHECK(str01.lastIndexOf(&str04) < 0);
	CHECK(str01.lastIndexOf(&str06) < 0);
	CHECK(str01.lastIndexOf(&str07) < 0);
	CHECK(str01.lastIndexOf(&str08) < 0);
}

TEST(UnicodeStringTestGroup, insert){
	UnicodeString str01(L"Hello");
	UnicodeString str02(L"World");
	UnicodeString str03(L"HelloWorld");

	str01.insert(str01.length(), &str02);
	CHECK(str01.equals(&str03));

	UnicodeString strap(L"Hello");
	strap.append(&str02);
	CHECK(strap.equals(&str03));

	UnicodeString strins(L"Hello");
	strins.insert(strins.length(), L"World", 0, 5);
	CHECK(strins.equals(&str03));
}

