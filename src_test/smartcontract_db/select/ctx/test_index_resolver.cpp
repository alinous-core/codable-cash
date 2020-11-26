/*
 * test_index_resolver.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"


TEST_GROUP(TestIndexResolverGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};
