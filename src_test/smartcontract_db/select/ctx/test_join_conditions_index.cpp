/*
 * test_join_conditions_index.cpp
 *
 *  Created on: 2020/12/17
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"


TEST_GROUP(TestJoinConditionIndexGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

