/*
 * test_joinpart_left.cpp
 *
 *  Created on: 2020/08/26
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../toolkit/TestDbSchema01.h"

using namespace codablecash;

TEST_GROUP(TestJoinPartLeftGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};


TEST(TestJoinPartLeftGroup, case01){
	TestDbSchema01 schem(this->env);


}
