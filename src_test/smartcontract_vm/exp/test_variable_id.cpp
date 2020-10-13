/*
 * test_variable_id.cpp
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"

#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "lang/sc_expression/VariableIdentifier.h"

#include "engine/sc_analyze/AnalyzedType.h"

using namespace alinous;


TEST_GROUP(TestVariableIdGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVariableIdGroup, test01){
	VariableIdentifier* id = new VariableIdentifier(); __STP(id);
	AnalyzedType atype = id->getType(nullptr);

	CHECK(atype.getType() == AnalyzedType::TYPE_NONE)
}

