/*
 * test_btree.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btreekey/BtreeKeyFactory.h"
#include "test_utils/t_macros.h"

#include "btree/Btree.h"
#include "btree/BtreeConfig.h"
#include "btree/TreeNode.h"
#include "btree/DataNode.h"
#include "btree/exceptions.h"
#include "btree/NodeCursor.h"
#include "btree/NodePosition.h"
#include "btree/BtreeScanner.h"
#include "btree/NodeHandle.h"

#include "btree_cache/NodeCacheRef.h"

#include "btreekey/ULongKey.h"
#include "btreekey/InfinityKey.h"
#include "TempValue.h"

#include "random_access_file/DiskCacheManager.h"

#include "base/StackRelease.h"
#include "base/RawBitSet.h"

#include "base_io/ByteBuffer.h"

#include <stdlib.h>


using namespace alinous;

TEST_GROUP(TestBTreeGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestBTreeGroup, infinityKey){
	InfinityKey key;
	InfinityKey* key2 = dynamic_cast<InfinityKey*>(key.clone());
	ULongKey ulkey(100);

	CHECK(key.compareTo(key2) == 0)
	CHECK(key.compareTo(&ulkey) > 0)

	delete key2;
}

TEST(TestBTreeGroup, checkDataNode){
	TreeNode* node = new TreeNode(false, 4, new ULongKey(1), true);
	SynchronizedLock lock;
	NodeCacheRef ref(node, &lock);

	NodeHandle handle(&ref);

	Exception* ex = nullptr;
	try{
		NodeCursor::checkIsDataNode(&handle, __FILE__, __LINE__);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)
	delete ex;


}

TEST(TestBTreeGroup, casterror01){
	uint64_t fpos = 256;

	TreeNode* node = new TreeNode(false, 4, new ULongKey(1), true);
	node->setFpos(fpos);

	Exception* ex = nullptr;
	try{
		AbstractTreeNode::toDataNode(node);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)
	delete ex;

	delete node;
}

TEST(TestBTreeGroup, casterror02){
	uint64_t fpos = 256;

	DataNode* node = new DataNode(new ULongKey(1));
	node->setFpos(fpos);

	CHECK(node->isData())

	Exception* ex = nullptr;
	try{
		AbstractTreeNode::toTreeNode(node);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)
	delete ex;

	delete node;
}

TEST(TestBTreeGroup, structureerror01){

	Exception* ex;
	try{
		NodePosition::checkNoNull(nullptr, __FILE__, __LINE__);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestBTreeGroup, constract){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BtreeKeyFactory* factory = new BtreeKeyFactory();
	TmpValueFactory* dfactory = new TmpValueFactory();

	Btree btree(baseDir, &name, &cacheManager, factory, dfactory);

	BtreeConfig config;
	btree.create(&config);
}

TEST(TestBTreeGroup, open){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BtreeKeyFactory* factory = new BtreeKeyFactory();
	TmpValueFactory* dfactory = new TmpValueFactory();

	Btree btree(baseDir, &name, &cacheManager, factory, dfactory);

	BtreeConfig config;
	btree.create(&config);

	BtreeOpenConfig opconf;
	btree.open(&opconf);
	btree.close();
}

static void addKeyValue(uint64_t key, uint64_t value, Btree* btree){
	ULongKey lkey(key);
	TempValue tvalue(value);

	btree->insert(&lkey, &tvalue);
}


TEST(TestBTreeGroup, add01){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BtreeKeyFactory* factory = new BtreeKeyFactory();
	TmpValueFactory* dfactory = new TmpValueFactory();

	Btree btree(baseDir, &name, &cacheManager, factory, dfactory);

	BtreeConfig config;
	config.nodeNumber = 2;
	btree.create(&config);

	BtreeOpenConfig opconf;
	btree.open(&opconf);

	RawArrayPrimitive<uint64_t> answers(32);
	{
		addKeyValue(10, 10, &btree);
		addKeyValue(6, 6, &btree);
		addKeyValue(6, 6, &btree);

		addKeyValue(3, 3, &btree);
		addKeyValue(2, 2, &btree);
		addKeyValue(100, 100, &btree);

		answers.addElement(2);
		answers.addElement(3);
		answers.addElement(6);
		//answers.addElement(6);
		answers.addElement(10);
		answers.addElement(100);
	}

	{
		BtreeScanner* scanner = btree.getScanner();
		StackRelease<BtreeScanner> __st_scanner(scanner);

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
	{
		ULongKey lkey(7);

		BtreeScanner* scanner = btree.getScanner();
		StackRelease<BtreeScanner> __st_scanner(scanner);

		scanner->begin(&lkey);
		int i = 3;
		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
			uint64_t v = tmp->getValue();

			uint64_t a = answers.get(i++);
			CHECK(v == a)
		}
	}
	{
		ULongKey lkey(6);

		BtreeScanner* scanner = btree.getScanner();
		StackRelease<BtreeScanner> __st_scanner(scanner);

		scanner->begin(&lkey);
		int i = 2;
		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
			uint64_t v = tmp->getValue();

			uint64_t a = answers.get(i++);
			CHECK(v == a)
		}
	}
	{
		ULongKey lkey(1000);

		BtreeScanner* scanner = btree.getScanner();
		StackRelease<BtreeScanner> __st_scanner(scanner);

		scanner->begin(&lkey);
		CHECK(scanner->hasNext() == false)
	}

	{
		// irregular case
		BtreeScanner* scanner = btree.getScanner();
		StackRelease<BtreeScanner> __st_scanner(scanner);
		scanner->hasNext();
	}

	{
		ULongKey lkey(6);
		IBlockObject* obj = btree.findByKey(&lkey);
		const TempValue* tmp = dynamic_cast<const TempValue*>(obj);
		uint64_t v = tmp->getValue();
		CHECK(v == 6)

		delete obj;

		ULongKey lkey2(7);
		obj = btree.findByKey(&lkey2);
		CHECK(obj == nullptr)
	}

	btree.close();
}

TEST(TestBTreeGroup, add02){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BtreeKeyFactory* factory = new BtreeKeyFactory();
	TmpValueFactory* dfactory = new TmpValueFactory();

	Btree btree(baseDir, &name, &cacheManager, factory, dfactory);

	BtreeConfig config;
	config.nodeNumber  = 3;
	btree.create(&config);

	BtreeOpenConfig opconf;
	btree.open(&opconf);

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
		BtreeScanner* scanner = btree.getScanner();
		StackRelease<BtreeScanner> __st_scanner(scanner);

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

	{
		// irregular case
		BtreeScanner* scanner = btree.getScanner();
		StackRelease<BtreeScanner> __st_scanner(scanner);
		scanner->hasNext();
	}

	btree.close();
}

TEST(TestBTreeGroup, remove01){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BtreeKeyFactory* factory = new BtreeKeyFactory();
	TmpValueFactory* dfactory = new TmpValueFactory();

	Btree btree(baseDir, &name, &cacheManager, factory, dfactory);

	BtreeConfig config;
	config.nodeNumber  = 3;
	btree.create(&config);

	BtreeOpenConfig opconf;
	btree.open(&opconf);

	RawArrayPrimitive<uint64_t> answers(32);
	{
		addKeyValue(10, 10, &btree);
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
		//answers.addElement(7);
		//answers.addElement(8);
		//answers.addElement(9);
		//answers.addElement(10);
		answers.addElement(11);
		answers.addElement(12);
		answers.addElement(13);
		answers.addElement(14);
		answers.addElement(50);
		answers.addElement(100);

		{
			ULongKey lkey(7);
			btree.remove(&lkey);
		}
		{
			ULongKey lkey(7000);
			btree.remove(&lkey);
		}
		{
			ULongKey lkey8(8);
			btree.remove(&lkey8);
			ULongKey lkey9(9);
			btree.remove(&lkey9);
			ULongKey lkey10(10);
			btree.remove(&lkey10);
		}

		{
			BtreeScanner* scanner = btree.getScanner();
			StackRelease<BtreeScanner> __st_scanner(scanner);

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

	btree.close();
}

static void removeValue(uint64_t value, Btree* btree){
	ULongKey lkey(value);
	btree->remove(&lkey);
}

TEST(TestBTreeGroup, remove02){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BtreeKeyFactory* factory = new BtreeKeyFactory();
	TmpValueFactory* dfactory = new TmpValueFactory();

	Btree btree(baseDir, &name, &cacheManager, factory, dfactory);

	BtreeConfig config;
	config.nodeNumber  = 2;
	btree.create(&config);

	BtreeOpenConfig opconf;
	btree.open(&opconf);

	RawArrayPrimitive<uint64_t> answers(32);
	{
		addKeyValue(1, 1, &btree);
		addKeyValue(2, 2, &btree);
		addKeyValue(3, 3, &btree);
		addKeyValue(4, 4, &btree);
		addKeyValue(5, 5, &btree);
		addKeyValue(6, 6, &btree);

		removeValue(1, &btree);
		removeValue(2, &btree);
		removeValue(3, &btree);

		answers.addElement(4);
		answers.addElement(5);
		answers.addElement(6);
	}

	{
		BtreeScanner* scanner = btree.getScanner();
		StackRelease<BtreeScanner> __st_scanner(scanner);

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

	btree.close();
}


