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

#include "base/RawArrayPrimitive.h"

#include "base/StackRelease.h"

#include "btree_memory/MemoryBtreeScanner.h"
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

	BTreeOnMemory btree(config, factory);
}

static void addKeyValue(uint64_t key, uint64_t value, BTreeOnMemory* btree){
	ULongKey lkey(key);
	TempValue* tvalue = new TempValue(value);

	btree->insert(&lkey, tvalue);
}

TEST(TestBTreeMemoryGroup, add01){
	BtreeConfig* config = new BtreeConfig();
	config->nodeNumber = 2;
	BtreeKeyFactory* factory = new BtreeKeyFactory();

	BTreeOnMemory btree(config, factory);

	RawArrayPrimitive<uint64_t> answers(32);
	{
		addKeyValue(10, 10, &btree);
		addKeyValue(6, 6, &btree);
		addKeyValue(3, 3, &btree);

		answers.addElement(3);
		answers.addElement(6);
		answers.addElement(10);

	}

	{
		MemoryBtreeScanner* scanner = btree.getScanner();
		StackRelease<MemoryBtreeScanner> __st_scanner(scanner);

		scanner->begin();
		int i = 0;
		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
			uint64_t v = tmp->getValue();

			uint64_t a = answers.get(i++);
			CHECK(v == a)
		}
	}
}

