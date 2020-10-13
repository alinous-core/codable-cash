/*
 * test_analyzed_type.cpp
 *
 *  Created on: 2020/03/02
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "base/UnicodeString.h"

#include "../VmTestUtils.h"
#include "engine/sc_analyze/AnalyzedClass.h"

using namespace alinous;

TEST_GROUP(TestAnalyzedtypeGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestAnalyzedtypeGroup, boolean_str){
	AnalyzedType atype(AnalyzedType::TYPE_BOOL);
	UnicodeString ans(L"boolean");

	const UnicodeString* str = atype.stringName();
	CHECK(str->equals(&ans));
}

TEST(TestAnalyzedtypeGroup, byte_str){
	AnalyzedType atype(AnalyzedType::TYPE_BYTE);
	UnicodeString ans(L"byte");

	const UnicodeString* str = atype.stringName();
	CHECK(str->equals(&ans));
}

TEST(TestAnalyzedtypeGroup, char_str){
	AnalyzedType atype(AnalyzedType::TYPE_CHAR);
	UnicodeString ans(L"char");

	const UnicodeString* str = atype.stringName();
	CHECK(str->equals(&ans));
}

TEST(TestAnalyzedtypeGroup, short_str){
	AnalyzedType atype(AnalyzedType::TYPE_SHORT);
	UnicodeString ans(L"short");

	const UnicodeString* str = atype.stringName();
	CHECK(str->equals(&ans));
}

TEST(TestAnalyzedtypeGroup, long_str){
	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	UnicodeString ans(L"long");

	const UnicodeString* str = atype.stringName();
	CHECK(str->equals(&ans));
}

TEST(TestAnalyzedtypeGroup, string_str){
	AnalyzedType atype(AnalyzedType::TYPE_STRING);
	UnicodeString ans(L"String");

	const UnicodeString* str = atype.stringName();
	CHECK(str->equals(&ans));
}

TEST(TestAnalyzedtypeGroup, void_str){
	AnalyzedType atype(AnalyzedType::TYPE_VOID);
	UnicodeString ans(L"void");

	const UnicodeString* str = atype.stringName();
	CHECK(str->equals(&ans));
}

TEST(TestAnalyzedtypeGroup, void_sigmakeObjectStringNull){
	AnalyzedType atype(AnalyzedType::TYPE_OBJECT);
	UnicodeString ans(L"null");

	const UnicodeString* str = atype.stringName();
	CHECK(str->equals(&ans));
}

///////////////////////////////////////////////////////////

TEST(TestAnalyzedtypeGroup, bool_sig){
	AnalyzedType atype(AnalyzedType::TYPE_BOOL);

	const UnicodeString* str = atype.getSignatureName();
	CHECK(str->equals(&AnalyzedType::SIG_BOOL));
}


TEST(TestAnalyzedtypeGroup, byte_sig){
	AnalyzedType atype(AnalyzedType::TYPE_BYTE);

	const UnicodeString* str = atype.getSignatureName();
	CHECK(str->equals(&AnalyzedType::SIG_BYTE));
}

TEST(TestAnalyzedtypeGroup, char_sig){
	AnalyzedType atype(AnalyzedType::TYPE_CHAR);

	const UnicodeString* str = atype.getSignatureName();
	CHECK(str->equals(&AnalyzedType::SIG_CHAR));
}

TEST(TestAnalyzedtypeGroup, short_sig){
	AnalyzedType atype(AnalyzedType::TYPE_SHORT);

	const UnicodeString* str = atype.getSignatureName();
	CHECK(str->equals(&AnalyzedType::SIG_SHORT));
}

TEST(TestAnalyzedtypeGroup, long_sig){
	AnalyzedType atype(AnalyzedType::TYPE_LONG);

	const UnicodeString* str = atype.getSignatureName();
	CHECK(str->equals(&AnalyzedType::SIG_LONG));
}

TEST(TestAnalyzedtypeGroup, string_sig){
	AnalyzedType atype(AnalyzedType::TYPE_STRING);

	const UnicodeString* str = atype.getSignatureName();
	CHECK(str->equals(&AnalyzedType::SIG_STRING));
}

TEST(TestAnalyzedtypeGroup, void_sig){
	AnalyzedType atype(AnalyzedType::TYPE_VOID);

	const UnicodeString* str = atype.getSignatureName();
	CHECK(str->equals(&AnalyzedType::SIG_VOID));
}

//////////////////////////////////////////////
TEST(TestAnalyzedtypeGroup, equal_true){
	AnalyzedType atype(AnalyzedType::TYPE_VOID);
	AnalyzedType atype2(AnalyzedType::TYPE_VOID);

	bool res = atype.equals(&atype2);
	CHECK(res)
}

TEST(TestAnalyzedtypeGroup, equal_false){
	AnalyzedType atype(AnalyzedType::TYPE_VOID);
	AnalyzedType atype2(AnalyzedType::TYPE_STRING);

	bool res = atype.equals(&atype2);
	CHECK(!res)
}
 ///////////////////////////////////////////////////

TEST(TestAnalyzedtypeGroup, objectSig){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)


	UnicodeString clazz(L"test.fw.SmartContract");
	AnalyzedType* atype = util.findClassDeclare(&clazz); __STP(atype);
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	const UnicodeString* str = atype->getSignatureName();
	UnicodeString clazzsig(L"Ltest.fw.SmartContract;");
	CHECK(str->equals(&clazzsig));
}

