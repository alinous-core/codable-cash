/*
 * test_superclass_method_access.cpp
 *
 *  Created on: 2020/05/05
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

#include "sc_analyze/AnalyzedType.h"
#include "variable_access/ClassTypeAccess.h"

using namespace alinous;


TEST_GROUP(TestSuperClassMethodAccessGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestSuperClassMethodAccessGroup, case01){

}
