/*
 * test_ref_factory.cpp
 *
 *  Created on: 2020/03/09
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "../VmTestUtils.h"

#include "instance/VmClassInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/ObjectReference.h"
#include "instance/instance_ref/RefereceFactory.h"


using namespace alinous;

TEST_GROUP(TestRefFactoryGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestRefFactoryGroup, testBool){
	VirtualMachine vm(1024 * 10);
	AnalyzedType atype(AnalyzedType::TYPE_BOOL);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(nullptr, &atype, &vm); __STP(ref);
	uint8_t t = ref->getType();
	CHECK(t == VmInstanceTypesConst::REF_BOOL)
}

TEST(TestRefFactoryGroup, testObject){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(nullptr, class1, util.vm); __STP(ref);
	uint8_t t = ref->getType();
	CHECK(t == VmInstanceTypesConst::REF_OBJ)
}

TEST(TestRefFactoryGroup, testArray){
	VirtualMachine vm(1024 * 10);
	AnalyzedType atype(AnalyzedType::TYPE_BOOL);
	atype.setDim(1);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(nullptr, &atype, &vm); __STP(ref);
	uint8_t t = ref->getType();
	CHECK(t == VmInstanceTypesConst::REF_ARRAY)
}
