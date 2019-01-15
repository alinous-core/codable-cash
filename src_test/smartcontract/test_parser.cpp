/*
 * test_parser.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "sc_parser/SmartContractParser.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestParserGroup) {
	TEST_SETUP(){
		this->env->setup();
	}
	TEST_TEARDOWN(){
		this->env->teardown();
	}
};


TEST(TestParserGroup, construct){

}
