/*
 * test_local_oid.cpp
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

TEST_GROUP(TestLocalOidGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestLocalOidGroup, case01){

}
