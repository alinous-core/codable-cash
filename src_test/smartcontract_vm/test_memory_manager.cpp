/*
 * test_memory_manager.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */



#include "test_utils/t_macros.h"

#include "memory/VmMemoryManager.h"

using namespace alinous;


TEST_GROUP(TestMemoryGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

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

