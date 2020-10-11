/*
 * test_exec_alter_modify_index_check.cpp
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../toolkit_alter/TestDbSchemaAlterModifyIndexCheck.h"

using namespace codablecash;

TEST_GROUP(TestExecAlterModifyIndexCheckGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestExecAlterModifyIndexCheckGroup, case01){
	TestDbSchemaAlterModifyIndexCheck tester(env);
	tester.init(1024*10);
	tester.insert01();
}

