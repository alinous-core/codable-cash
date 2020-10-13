/*
 * test_superclass_method_access.cpp
 *
 *  Created on: 2020/05/05
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"

#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "base/UnicodeString.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "vm/variable_access/ClassTypeAccess.h"

using namespace alinous;


TEST_GROUP(TestSuperClassMethodAccessGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestSuperClassMethodAccessGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/superclass/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"count");
	CHECK(iresult == 20);
}

TEST(TestSuperClassMethodAccessGroup, case02_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/superclass/case02_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

}
