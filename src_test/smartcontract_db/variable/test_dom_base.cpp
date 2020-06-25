/*
 * test_dom_base.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

#include "instance_dom/DomVariableInstance.h"

using namespace alinous;

TEST_GROUP(TestDomBaseGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestDomBaseGroup, case01){
	VirtualMachine vm(1024 * 10);

	DomVariableInstance* dom = new(&vm) DomVariableInstance(&vm);

	delete dom;
}
