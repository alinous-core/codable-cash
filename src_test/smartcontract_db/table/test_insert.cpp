/*
 * test_insert.cpp
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

using namespace alinous;
//using namespace codablecash;

TEST_GROUP(TestInsertGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestInsertGroup, case01) {

}
