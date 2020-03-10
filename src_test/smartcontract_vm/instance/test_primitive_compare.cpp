/*
 * test_primitive_compare.cpp
 *
 *  Created on: 2020/03/09
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "../VmTestUtils.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref/RefereceFactory.h"

#include "instance_gc/GcManager.h"

#include "instance_ref/PrimitiveReference.h"

using namespace alinous;

TEST_GROUP(TestPrimitiveCompareGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestPrimitiveCompareGroup, case01){

}

