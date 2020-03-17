/*
 * test_string_class.cpp
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"

#include "reserved_classes_string/StringClassDeclare.h"

using namespace alinous;

TEST_GROUP(TestStringClassGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStringClassGroup, construct){
	StringClassDeclare dec;
	const UnicodeString* str = dec.getName();

	CHECK(str->equals(&StringClassDeclare::NAME))
}

TEST(TestStringClassGroup, base01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/reserved_classes/resources/string/base01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

