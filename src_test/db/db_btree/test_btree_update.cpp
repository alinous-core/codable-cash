/*
 * test_btree_update.cpp
 *
 *  Created on: 2020/06/07
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

TEST_GROUP(TestBTreeUpdateGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

static void addKeyValue(uint64_t key, uint64_t value, Btree* btree){
	ULongKey lkey(key);
	TempValue tvalue(value);

	btree->putData(&lkey, &tvalue);
}

TEST(TestBTreeUpdateGroup, case01){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BtreeKeyFactory* factory = new BtreeKeyFactory(); __STP(factory);
	TmpValueFactory* dfactory = new TmpValueFactory(); __STP(dfactory);

	Btree btree(baseDir, &name, &cacheManager, factory, dfactory);

	BtreeConfig config;
	config.nodeNumber = 2;
	btree.create(&config);

	BtreeOpenConfig opconf;
	btree.open(&opconf);

	{
		addKeyValue(1, 2, &btree);
		addKeyValue(1, 10, &btree);

		ULongKey lkey(1);
		IBlockObject* data = btree.findByKey(&lkey); __STP(data);
		TempValue* tvalue = dynamic_cast<TempValue*>(data);

		CHECK(tvalue->getValue() == 10)

	}

	btree.close();
}
