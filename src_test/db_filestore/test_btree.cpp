/*
 * test_btree.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "btree/Btree.h"


#include "base/StackRelease.h"
#include "base/RawBitSet.h"

#include "base_io/ByteBuffer.h"

#include <stdlib.h>


using namespace alinous;

TEST_GROUP(TestBTree) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestBTree, constract){

}
