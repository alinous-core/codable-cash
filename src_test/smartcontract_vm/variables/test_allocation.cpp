/*
 * test_allocation.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

using namespace alinous;


TEST_GROUP(TestAllocationStmtGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestAllocationStmtGroup, primitiveAllocation){
	// FIXME test

}