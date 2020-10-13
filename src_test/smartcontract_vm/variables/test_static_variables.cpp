/*
 * test_static_variables.cpp
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "ext_binary/AbstractExtObject.h"
#include "ext_binary/ExtClassObject.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "engine/sc_analyze/ValidationError.h"

#include "../VmTestUtils.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "instance/instance_ref_class_static/ClassTypeReference.h"

#include "instance/instance_ref/VmRootReference.h"

using namespace alinous;


TEST_GROUP(TestStaticVariablesGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStaticVariablesGroup, ClassTypeReferenceMisc){
	VirtualMachine vm(1024 * 10);
	VmRootReference* root = new(&vm) VmRootReference(&vm); __STP(root);

	AnalyzedType at(AnalyzedType::TYPE_STRING);

	ClassTypeReference classRef(root, &vm, &at);

	CHECK(classRef.instValueCompare(nullptr) == 0);
	CHECK(classRef.wrap(nullptr, &vm) == 0);
	CHECK(classRef.getRuntimeType().equals(&at));
	CHECK(classRef.getInstType() == classRef.getInstType());
	CHECK(classRef.getInstReferences() == nullptr);
	CHECK(!classRef.instIsNull());
	CHECK(classRef.instToClassExtObject(nullptr, nullptr) == nullptr);

	classRef.resetOnGc();
}

TEST(TestStaticVariablesGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/static/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

