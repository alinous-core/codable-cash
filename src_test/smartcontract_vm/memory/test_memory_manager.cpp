/*
 * test_memory_manager.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */



#include "test_utils/t_macros.h"

#include "vm/memory/VmMemoryManager.h"
#include "base/StackRelease.h"

#include "base/Exception.h"
#include "vm/exceptions.h"

using namespace alinous;


TEST_GROUP(TestMemoryGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestMemoryGroup, testex){
	testException<VmMemoryAllocationException>();
}

TEST(TestMemoryGroup, construct){
	VmMemoryManager* vm = new VmMemoryManager(1024);
	delete vm;
}

TEST(TestMemoryGroup, malloc01){
	VmMemoryManager* vm = new VmMemoryManager(1024);
	char* ptr = vm->malloc(32);

	int size = vm->getSize(ptr);
	CHECK(size == 32 + sizeof(uint32_t))

	vm->free(ptr);

	delete vm;
}

TEST(TestMemoryGroup, malloc01error){
	Exception* ex = nullptr;

	VmMemoryManager* vm = new VmMemoryManager(1024);
	__STP(vm);

	try{
		vm->malloc(1025);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestMemoryGroup, malloc02error){
	Exception* ex = nullptr;
	int seg = 6;
	int size = seg* (2 + sizeof(uint32_t));
	VmMemoryManager* vm = new VmMemoryManager(size); __STP(vm);

	try{
		char* ptr01 = vm->malloc(2);
		char* ptr02 = vm->malloc(2);
		char* ptr03 = vm->malloc(2);
		char* ptr04 = vm->malloc(2);
		char* ptr05 = vm->malloc(2);
		char* ptr06 = vm->malloc(2);

		vm->free(ptr02);
		vm->free(ptr04);
		vm->free(ptr06);

		vm->malloc(4);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

