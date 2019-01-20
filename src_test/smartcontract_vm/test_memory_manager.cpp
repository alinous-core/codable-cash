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
	VmMemoryManager* vm = new VmMemoryManager();
	delete vm;
}


