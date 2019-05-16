/*
 * test_main_block.cpp
 *
 *  Created on: 2019/03/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "main/MainBlock.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestMainBlock) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestMainBlock, construct){
	MainBlock block;

}
