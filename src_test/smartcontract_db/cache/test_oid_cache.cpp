/*
 * test_oid_cache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "transaction_cache/SwapCacheFactory.h"

TEST_GROUP(TestOidCacheGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestOidCacheGroup, case01){
	SwapCacheFactory factory;
}
