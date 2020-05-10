/*
 * test_sql_engine.cpp
 *
 *  Created on: 2020/05/10
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/File.h"
#include "base/StackRelease.h"

TEST_GROUP(TestDbEngineGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};
