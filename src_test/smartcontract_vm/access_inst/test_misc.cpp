/*
 * test_misc.cpp
 *
 *  Created on: 2020/04/21
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"

#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "base/UnicodeString.h"

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"

#include "instance/instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"

#include "vm/variable_access/ThisPointerAccess.h"
#include "vm/variable_access/StackVariableAccess.h"
#include "vm/variable_access/MemberVariableAccess.h"

using namespace alinous;


TEST_GROUP(TestAccessInstructionMiscGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestAccessInstructionMiscGroup, test01){
	ThisPointerAccess* ac = new ThisPointerAccess(); __STP(ac);
	CHECK(ac->getCodeElement() == nullptr);
}

TEST(TestAccessInstructionMiscGroup, test02){
	StackVariableAccess* ac = new StackVariableAccess(0, 0); __STP(ac);
	CHECK(ac->getCodeElement() == nullptr);
}

TEST(TestAccessInstructionMiscGroup, test03){
	MemberVariableAccess* ac = new MemberVariableAccess(nullptr); __STP(ac);
	CHECK(ac->getCodeElement() == nullptr);
}



