/*
 * test_compiler_utils.cpp
 *
 *  Created on: 2019/06/23
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "engine/sc/CompilationUnit.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc/exceptions.h"

TEST_GROUP(TestCompilerUtilsGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestCompilerUtilsGroup, isFqn){
	UnicodeString str(L"test.fw.clazz");
	UnicodeString strc(L"clazz");

	bool bl = TypeResolver::isFqn(&str);
	CHECK(bl);

	bl = TypeResolver::isFqn(&strc);
	CHECK(!bl);
}

TEST(TestCompilerUtilsGroup, testGetPackage){
	UnicodeString str(L"test.fw.clazz");
	UnicodeString pstr(L"test.fw");
	UnicodeString cstr(L"clazz");

	UnicodeString* package = TypeResolver::getPackageName(&str); __STP(package);
	bool bl = pstr.equals(package);
	CHECK(bl);

	UnicodeString* package2 = TypeResolver::getPackageName(&cstr);
	CHECK(package2 == nullptr);
}

TEST(TestCompilerUtilsGroup, testGetClassName){
	UnicodeString str(L"test.fw.clazz");
	UnicodeString cstr(L"clazz");

	UnicodeString* clazz = TypeResolver::getClassName(&str); __STP(clazz);
	bool bl = cstr.equals(clazz);
	CHECK(bl);

	UnicodeString* clazz2 = TypeResolver::getClassName(&cstr);
	CHECK(clazz2 == nullptr);
}
