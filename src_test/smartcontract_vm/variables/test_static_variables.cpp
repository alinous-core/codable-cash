/*
 * test_static_variables.cpp
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "instance_ref/VmRootReference.h"
#include "instance/VmClassInstance.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze_functions/VTableRegistory.h"

#include "ext_binary/AbstractExtObject.h"
#include "ext_binary/ExtClassObject.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "sc_analyze/ValidationError.h"
using namespace alinous;


TEST_GROUP(TestStaticVariablesGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStaticVariablesGroup, case01){

}

