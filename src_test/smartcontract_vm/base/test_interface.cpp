/*
 * test_interface.cpp
 *
 *  Created on: 2020/03/04
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "../VmTestUtils.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/AnalyzedType.h"

using namespace alinous;

TEST_GROUP(TestInterfaceGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestInterfaceGroup, base01){

}

