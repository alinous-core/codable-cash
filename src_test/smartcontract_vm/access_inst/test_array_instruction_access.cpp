/*
 * test_array_instruction_access.cpp
 *
 *  Created on: 2020/04/20
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

#include "instance_exception/NullPointerExceptionClassDeclare.h"

#include "instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"
using namespace alinous;


TEST_GROUP(TestArrayInstAccessGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestArrayInstAccessGroup, case01){

}
