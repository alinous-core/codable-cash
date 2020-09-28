/*
 * test_btree_memory.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "btreekey/BtreeKeyFactory.h"
#include "btreekey/ULongKey.h"

#include "btree_memory/BtreeOnMemory.h"

#include "TempValue.h"

#include "btree/BtreeConfig.h"
#include "base/RawArrayPrimitive.h"
#include "base/StackRelease.h"

#include "btree_memory/MemoryBtreeScanner.h"
#include "btree_memory/MemoryDataNode.h"
#include "btree_memory/MemoryTreeNode.h"

using namespace alinous;

TEST_GROUP(TestBTreeMemoryGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestBTreeMemoryGroup, constract){
	BtreeConfig* config = new BtreeConfig();
	BtreeKeyFactory* factory = new BtreeKeyFactory(); __STP(factory);

	BtreeOnMemory btree(config, factory);
}

TEST(TestBTreeMemoryGroup, misc01){
	MemoryDataNode n(nullptr);

	CHECK(n.isData());
}

TEST(TestBTreeMemoryGroup, misc02){
	MemoryTreeNode n(1, nullptr, false);

	CHECK(!n.isData());
}

static void addKeyValue(uint64_t key, uint64_t value, BtreeOnMemory* btree){
	ULongKey lkey(key);
	TempValue* tvalue = new TempValue(value); __STP(tvalue);

	btree->putData(&lkey, tvalue);
}

TEST(TestBTreeMemoryGroup, emptyScan01){
	BtreeConfig* config = new BtreeConfig();
	config->nodeNumber = 2;
	BtreeKeyFactory* factory = new BtreeKeyFactory(); __STP(factory);

	BtreeOnMemory btree(config, factory);
	{
		MemoryBtreeScanner* scanner = btree.getScanner();
		StackRelease<MemoryBtreeScanner> __st_scanner(scanner);

		scanner->begin();

		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const AbstractBtreeKey* k = scanner->nextKey();

		}
	}
}

TEST(TestBTreeMemoryGroup, add01){
	BtreeConfig* config = new BtreeConfig();
	config->nodeNumber = 2;
	BtreeKeyFactory* factory = new BtreeKeyFactory(); __STP(factory);

	BtreeOnMemory btree(config, factory);

	RawArrayPrimitive<uint64_t> answers(32);
	{
		addKeyValue(10, 10, &btree);
		addKeyValue(6, 6, &btree);
		addKeyValue(3, 3, &btree);

		addKeyValue(6, 6, &btree);

		addKeyValue(2, 2, &btree);
		addKeyValue(100, 100, &btree);

		answers.addElement(2);
		answers.addElement(3);
		answers.addElement(6);
		answers.addElement(10);
		answers.addElement(100);
	}

	{
		MemoryBtreeScanner* scanner = btree.getScanner();
		StackRelease<MemoryBtreeScanner> __st_scanner(scanner);

		scanner->begin();
		int i = 0;
		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const AbstractBtreeKey* k = scanner->nextKey();

			const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
			uint64_t v = tmp->getValue();

			const ULongKey* lk = dynamic_cast<const ULongKey*>(k);
			uint64_t kv = lk->getValue();

			uint64_t a = answers.get(i++);
			CHECK(v == a)
			CHECK(kv == a)
		}
	}

	{
		ULongKey lkey(7);

		MemoryBtreeScanner* scanner = btree.getScanner();
		StackRelease<MemoryBtreeScanner> __st_scanner(scanner);

		scanner->begin(&lkey);
		int i = 3;
		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const AbstractBtreeKey* k = scanner->nextKey();

			const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
			uint64_t v = tmp->getValue();

			const ULongKey* lk = dynamic_cast<const ULongKey*>(k);
			uint64_t kv = lk->getValue();

			uint64_t a = answers.get(i++);
			CHECK(v == a)
			CHECK(kv == a)
		}
	}

	{
		ULongKey lkey(6);

		MemoryBtreeScanner* scanner = btree.getScanner();
		StackRelease<MemoryBtreeScanner> __st_scanner(scanner);

		scanner->begin(&lkey);
		int i = 2;
		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const AbstractBtreeKey* k = scanner->nextKey();

			const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
			uint64_t v = tmp->getValue();

			const ULongKey* lk = dynamic_cast<const ULongKey*>(k);
			uint64_t kv = lk->getValue();

			uint64_t a = answers.get(i++);
			CHECK(v == a)
			CHECK(kv == a)
		}
	}

	{
		ULongKey lkey(1000);

		MemoryBtreeScanner* scanner = btree.getScanner();
		StackRelease<MemoryBtreeScanner> __st_scanner(scanner);

		scanner->begin(&lkey);
		CHECK(scanner->hasNext() == false)
	}
}

TEST(TestBTreeMemoryGroup, add02){
	BtreeConfig* config = new BtreeConfig();
	config->nodeNumber = 2;
	BtreeKeyFactory* factory = new BtreeKeyFactory(); __STP(factory);

	BtreeOnMemory btree(config, factory);

	RawArrayPrimitive<uint64_t> answers(32);
	{
		addKeyValue(10, 10, &btree);
		addKeyValue(6, 6, &btree);
		addKeyValue(6, 6, &btree);

		addKeyValue(3, 3, &btree);
		addKeyValue(2, 2, &btree);
		addKeyValue(100, 100, &btree);
		addKeyValue(50, 50, &btree);
		addKeyValue(7, 7, &btree);
		addKeyValue(8, 8, &btree);
		addKeyValue(9, 9, &btree);
		addKeyValue(11, 11, &btree);
		addKeyValue(12, 12, &btree);
		addKeyValue(13, 13, &btree);
		addKeyValue(14, 14, &btree);


		answers.addElement(2);
		answers.addElement(3);
		answers.addElement(6);
		answers.addElement(7);
		answers.addElement(8);
		answers.addElement(9);
		answers.addElement(10);
		answers.addElement(11);
		answers.addElement(12);
		answers.addElement(13);
		answers.addElement(14);
		answers.addElement(50);
		answers.addElement(100);
	}

	{
		MemoryBtreeScanner* scanner = btree.getScanner();
		StackRelease<MemoryBtreeScanner> __st_scanner(scanner);

		scanner->begin();
		int i = 0;
		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const AbstractBtreeKey* k = scanner->nextKey();

			const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
			uint64_t v = tmp->getValue();

			const ULongKey* lk = dynamic_cast<const ULongKey*>(k);
			uint64_t kv = lk->getValue();

			uint64_t a = answers.get(i++);
			CHECK(v == a)
			CHECK(kv == a)
		}

		CHECK(i == answers.size())
	}
}

TEST(TestBTreeMemoryGroup, add03){
	BtreeConfig* config = new BtreeConfig();
	config->nodeNumber = 3;
	BtreeKeyFactory* factory = new BtreeKeyFactory(); __STP(factory);

	BtreeOnMemory btree(config, factory);

	RawArrayPrimitive<uint64_t> answers(32);
	{
		addKeyValue(10, 10, &btree);
		addKeyValue(6, 6, &btree);
		addKeyValue(6, 6, &btree);

		addKeyValue(3, 3, &btree);
		addKeyValue(2, 2, &btree);
		addKeyValue(100, 100, &btree);
		addKeyValue(50, 50, &btree);
		addKeyValue(7, 7, &btree);
		addKeyValue(8, 8, &btree);
		addKeyValue(9, 9, &btree);
		addKeyValue(11, 11, &btree);
		addKeyValue(12, 12, &btree);
		addKeyValue(13, 13, &btree);
		addKeyValue(14, 14, &btree);


		answers.addElement(2);
		answers.addElement(3);
		answers.addElement(6);
		answers.addElement(7);
		answers.addElement(8);
		answers.addElement(9);
		answers.addElement(10);
		answers.addElement(11);
		answers.addElement(12);
		answers.addElement(13);
		answers.addElement(14);
		answers.addElement(50);
		answers.addElement(100);
	}

	{
		MemoryBtreeScanner* scanner = btree.getScanner();
		StackRelease<MemoryBtreeScanner> __st_scanner(scanner);

		scanner->begin();
		int i = 0;
		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const AbstractBtreeKey* k = scanner->nextKey();

			const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
			uint64_t v = tmp->getValue();

			const ULongKey* lk = dynamic_cast<const ULongKey*>(k);
			uint64_t kv = lk->getValue();

			uint64_t a = answers.get(i++);
			CHECK(v == a)
			CHECK(kv == a)
		}

		CHECK(i == answers.size())
	}
}

TEST(TestBTreeMemoryGroup, find01){
	BtreeConfig* config = new BtreeConfig();
	config->nodeNumber = 3;
	BtreeKeyFactory* factory = new BtreeKeyFactory(); __STP(factory);

	BtreeOnMemory btree(config, factory);
	{
		addKeyValue(10, 10, &btree);
		addKeyValue(6, 6, &btree);
		addKeyValue(6, 6, &btree);

		addKeyValue(3, 3, &btree);
		addKeyValue(2, 2, &btree);
		addKeyValue(100, 100, &btree);
		addKeyValue(50, 50, &btree);
		addKeyValue(7, 7, &btree);
		addKeyValue(8, 8, &btree);
		addKeyValue(9, 9, &btree);
		addKeyValue(11, 11, &btree);
		addKeyValue(12, 12, &btree);
		addKeyValue(13, 13, &btree);
		addKeyValue(14, 14, &btree);
	}

	ULongKey lkey(6);
	const IBlockObject* obj = btree.findByKey(&lkey);

	const TempValue* tvalue = dynamic_cast<const TempValue*>(obj);
	CHECK(tvalue->getValue() == 6);
}

TEST(TestBTreeMemoryGroup, find02){
	BtreeConfig* config = new BtreeConfig();
	config->nodeNumber = 3;
	BtreeKeyFactory* factory = new BtreeKeyFactory(); __STP(factory);

	BtreeOnMemory btree(config, factory);

	ULongKey lkey(6);
	const IBlockObject* obj = btree.findByKey(&lkey);
	CHECK(obj == nullptr);
}

