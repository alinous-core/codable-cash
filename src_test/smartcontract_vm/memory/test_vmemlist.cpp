/*
 * test_vmemlist.cpp
 *
 *  Created on: 2019/06/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "instance/instance_parts/VmMalloc.h"
#include "instance/instance_parts/VMemList.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_parts/VMemPrimitiveList.h"
using namespace alinous;

TEST_GROUP(TestVmMemList) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVmMemList, construct){
	VirtualMachine vm(1024);

	PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, 1);
	VMemList<PrimitiveReference> list(&vm);

	CHECK(ref->getIntValue() == 1)

	delete ref;
}

TEST(TestVmMemList, test02){
	VirtualMachine vm(1024);

	PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, 1);
	CHECK(ref->getIntValue() == 1)

	VMemList<PrimitiveReference>* list = new(&vm) VMemList<PrimitiveReference>(&vm);
	list->addElement(ref);

	delete ref;
	delete list;
}

TEST(TestVmMemList, testAddNullptr){
	VirtualMachine vm(1024 * 4);

	VMemList<PrimitiveReference>* list = new(&vm) VMemList<PrimitiveReference>(&vm, 2);
	int maxLoop = 10;
	for(int i = 0; i != maxLoop; ++i){
		//PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, 1);
		list->addElement(nullptr);
	}


	list->deleteElements();
	delete list;

}

TEST(TestVmMemList, testAddRefptr){
	VirtualMachine vm(1024 * 4);

	VMemList<PrimitiveReference>* list = new(&vm) VMemList<PrimitiveReference>(&vm, 2);
	int maxLoop = 10;
	for(int i = 0; i != maxLoop; ++i){
		PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, 1);
		list->addElement(ref);
	}


	list->deleteElements();
	delete list;

}

TEST(TestVmMemList, testPrimitive01){
	VirtualMachine vm(1024 * 4);

	VMemPrimitiveList<int>* list = new(&vm) VMemPrimitiveList<int>(&vm, 2);

	int maxLoop = 10;
	for(int i = 0; i != maxLoop; ++i){
		list->addElement(i);
	}

	delete list;
}

