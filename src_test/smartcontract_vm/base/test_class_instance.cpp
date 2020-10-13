/*
 * test_class_instance.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "instance/VmClassInstance.h"
#include "vm/VirtualMachine.h"

#include "base/Exception.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "engine/sc_analyze/AnalyzedClass.h"

#include "instance/VmInstanceTypesConst.h"
using namespace alinous;


TEST_GROUP(TestInstanceGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestInstanceGroup, construct){
	VirtualMachine vm(1024);
	AnalyzedClass clazz(nullptr);

	VmClassInstance* inst = new(&vm) VmClassInstance(&clazz, &vm);
	CHECK(inst->isReference() == false)

	delete inst;
}

TEST(TestInstanceGroup, constructError){
	VirtualMachine vm(2);
	AnalyzedClass clazz(nullptr);

	VmClassInstance* inst = nullptr;
	Exception* ex = nullptr;
	try {
		inst = new(&vm) VmClassInstance(&clazz, &vm);
	}
	catch(Exception* e){
		ex = e;
		delete inst;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestInstanceGroup, constructRef){
	PrimitiveReference ref(VmInstanceTypesConst::REF_BYTE);
}
