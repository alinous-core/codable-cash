/*
 * test_btree_memory.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "btreekey/BtreeKeyFactory.h"
#include "btreekey/ULongKey.h"

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

static void addKeyValue(uint64_t key, uint64_t value, BTreeOnMemory* btree){
	ULongKey lkey(key);
	TempValue* tvalue = new TempValue(value);

	btree->insert(&lkey, tvalue);
}

