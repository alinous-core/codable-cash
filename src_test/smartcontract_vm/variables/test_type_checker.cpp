/*
 * test_type_checker.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "base/StackRelease.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "type_check/AnalyzedTypeChecker.h"


using namespace alinous;

TEST_GROUP(TestTypeCheckGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestTypeCheckGroup, construct){
	AnalyzedTypeChecker checker;
}
