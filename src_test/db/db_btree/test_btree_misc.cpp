/*
 * test_btree_misc.cpp
 *
 *  Created on: 2020/09/27
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"
#include "btree/BtreeConfig.h"

#include "base/StackRelease.h"

using namespace alinous;

TEST_GROUP(TestBTreeMiscGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestBTreeMiscGroup, case01){
	BtreeConfig config;

	BtreeConfig* config2 = dynamic_cast<BtreeConfig*>(config.copyData()); __STP(config2);

	CHECK(config.blockSize = config2->blockSize);
	CHECK(config.nodeNumber = config2->blockSize);
}
