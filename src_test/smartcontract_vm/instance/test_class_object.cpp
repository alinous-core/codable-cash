/*
 * test_class_object.cpp
 *
 *  Created on: 2020/03/10
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "../VmTestUtils.h"

#include "instance/VmClassInstance.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref/ObjectReference.h"
#include "instance_ref/RefereceFactory.h"

#include "instance_array/ArrayReference.h"

#include "instance_array/VmArrayInstanceUtils.h"

#include "instance_gc/GcManager.h"


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

	AnalyzedType* class1 = util.findClassDeclare(L"test.fw.base.BaseClass"); __STP(class1);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(nullptr, class1, util.vm);

	VmClassInstance* inst1 = VmClassInstance::createObject(class1->getAnalyzedClass(), util.vm);

	ref->substitute(inst1, util.vm);
	ref->substitute(inst1, util.vm);
	ref->substitute(nullptr, util.vm);

	GcManager* gc = util.vm->getGc();
	delete ref;

	gc->garbageCollect();

}


