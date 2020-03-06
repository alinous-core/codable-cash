/*
 * test_mul.cpp
 *
 *  Created on: 2020/03/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"

#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "base/UnicodeString.h"

#include "instance_exception/ZeroDivisionException.h"

using namespace alinous;


TEST_GROUP(TestMulGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestMulGroup, exceptions){
	testException<ZeroDivisionException>();
}
TEST(TestMulGroup, case01){ // int

}

