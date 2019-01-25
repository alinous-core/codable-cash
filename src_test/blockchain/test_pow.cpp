/*
 * test_pow.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "flash_pow/NanceCalc.h"
#include "test_utils/t_macros.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestPoW) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestPoW, calc){
	NanceCalc calc;

}
