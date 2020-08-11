/*
 * test_btree_memory.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "btreekey/BtreeKeyFactory.h"

#include "btree_memory/BTreeOnMemory.h"

#include "TempValue.h"

#include "btree/BtreeConfig.h"

using namespace alinous;

TEST_GROUP(TestBTreeMemoryGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestBTreeMemoryGroup, constract){
	BtreeConfig* config = new BtreeConfig();
	BtreeKeyFactory* factory = new BtreeKeyFactory();
	TmpValueFactory* dfactory = new TmpValueFactory();

	BTreeOnMemory btree(config, factory, dfactory);
}

