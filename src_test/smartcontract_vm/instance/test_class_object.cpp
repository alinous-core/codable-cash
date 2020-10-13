/*
 * test_class_object.cpp
 *
 *  Created on: 2020/03/10
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
#include "instance/instance_ref/RefereceFactory.h"

#include "instance/instance_array/ArrayReference.h"

#include "instance/instance_array/VmArrayInstanceUtils.h"

#include "instance/instance_gc/GcManager.h"

#include "instance/instance_ref/VmRootReference.h"

using namespace alinous;

TEST_GROUP(TestClassObjectGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestClassObjectGroup, substitute01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	VmRootReference* root = new(util.vm) VmRootReference(util.vm);
	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(root, class1, util.vm);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm);
	inst1->getInstReferences();

	ref->substitute(inst1, util.vm);
	ref->substitute(inst1, util.vm);
	ref->substitute(nullptr, util.vm);

	GcManager* gc = util.vm->getGc();
	delete ref;

	gc->garbageCollect();

	delete root;
}

TEST(TestClassObjectGroup, wrap01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	VmRootReference* root = new(util.vm) VmRootReference(util.vm);
	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm);
	AbstractReference* ref = inst1->wrap(root, util.vm);

	GcManager* gc = util.vm->getGc();

	gc->registerObject(ref);
	gc->removeObject(ref);

	gc->garbageCollect();

	delete ref;
	delete root;
}

TEST(TestClassObjectGroup, wrapToString01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	VmRootReference* root = new(util.vm) VmRootReference(util.vm);
	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm);
	AbstractReference* ref = inst1->wrap(root, util.vm);

	const UnicodeString* str = ref->toString();

	UnicodeString clazzName(L"test.fw.base.BaseClass");
	CHECK(str->equals(clazzName))

	GcManager* gc = util.vm->getGc();

	gc->registerObject(ref);
	gc->removeObject(ref);

	gc->garbageCollect();

	delete ref;
	delete root;
}

TEST(TestClassObjectGroup, wrapToString02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	GcManager* gc = util.vm->getGc();

	VmRootReference* root = new(util.vm) VmRootReference(util.vm);
	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm);
	AbstractReference* ref = inst1->wrap(root, util.vm);
	gc->registerObject(ref);

	ref->substitute(nullptr, util.vm);

	const UnicodeString* str = ref->toString();

	UnicodeString clazzName(L"null");
	CHECK(str->equals(clazzName))

	gc->removeObject(ref);

	gc->garbageCollect();

	delete ref;
	delete root;
}
