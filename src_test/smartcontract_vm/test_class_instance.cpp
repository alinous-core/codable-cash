/*
 * test_class_instance.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "instance/VmClassInstance.h"
#include "vm/VirtualMachine.h"

using namespace alinous;


TEST_GROUP(TestInstanceGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestInstanceGroup, construct){
	VirtualMachine vm(1024);

	VmClassInstance* inst = new(&vm) VmClassInstance();
	delete inst;
}

