/*
 * test_class_compare.cpp
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

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/ObjectReference.h"
using namespace alinous;

TEST_GROUP(TestClassCompareGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestClassCompareGroup, compareVmClassInstance01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm); __STP(inst1);
	VmClassInstance* inst2 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm); __STP(inst2);

	int diff = inst1->valueCompare(inst2);
	CHECK(diff != 0);

	diff = inst1->valueCompare(inst1);
	CHECK(diff == 0);
}

TEST(TestClassCompareGroup, compareObjectReference01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm); __STP(inst1);

	ObjectReference* ref1 = ObjectReference::createObjectReference(nullptr, inst1, util.vm); __STP(ref1);

	int diff = ref1->valueCompare(ref1->getInstance());
	CHECK(diff == 0);
}

TEST(TestClassCompareGroup, compareObjectReference02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm); __STP(inst1);

	ObjectReference* ref1 = ObjectReference::createObjectReference(nullptr, inst1, util.vm); __STP(ref1);
	ObjectReference* ref2 = ObjectReference::createObjectReference(nullptr, inst1, util.vm); __STP(ref2);

	int diff = ref1->valueCompare(ref2->getInstance());
	CHECK(diff == 0);
}

TEST(TestClassCompareGroup, compareObjectReference03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm); __STP(inst1);
	VmClassInstance* inst2 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm); __STP(inst2);

	ObjectReference* ref1 = ObjectReference::createObjectReference(nullptr, inst1, util.vm); __STP(ref1);
	ObjectReference* ref2 = ObjectReference::createObjectReference(nullptr, inst2, util.vm); __STP(ref2);

	int diff = ref1->valueCompare(ref2->getInstance());
	CHECK(diff != 0);
}

TEST(TestClassCompareGroup, compareObjectReference04){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm); __STP(inst1);

	ObjectReference* ref1 = ObjectReference::createObjectReference(nullptr, inst1, util.vm); __STP(ref1);
	ObjectReference* ref2 = ObjectReference::createObjectReference(nullptr, nullptr, util.vm); __STP(ref2);

	int diff = ref1->valueCompare(ref2->getInstance());
	CHECK(diff != 0);

	diff = ref2->valueCompare(ref1->getInstance());
	CHECK(diff != 0);
}

TEST(TestClassCompareGroup, compareObjectReference05){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	ObjectReference* ref1 = ObjectReference::createObjectReference(nullptr, nullptr, util.vm); __STP(ref1);
	ObjectReference* ref2 = ObjectReference::createObjectReference(nullptr, nullptr, util.vm); __STP(ref2);

	int diff = ref1->valueCompare(ref2->getInstance());
	CHECK(diff == 0);

	diff = ref2->valueCompare(ref1->getInstance());
	CHECK(diff == 0);
}

TEST(TestClassCompareGroup, compareObjectReference06){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm); __STP(inst1);
	ObjectReference* ref1 = ObjectReference::createObjectReference(nullptr, inst1, util.vm); __STP(ref1);

	int diff = ref1->valueCompare(inst1);
	CHECK(diff == 0);
}
