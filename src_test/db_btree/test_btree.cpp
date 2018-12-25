/*
 * test_btree.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "btree/Btree.h"
#include "btree/BtreeConfig.h"
#include "btreekey/BTreeKeyFactory.h"
#include "random_access_file/DiskCacheManager.h"

#include "base/StackRelease.h"
#include "base/RawBitSet.h"

#include "base_io/ByteBuffer.h"

#include <stdlib.h>


using namespace alinous;

TEST_GROUP(TestBTreeGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestBTreeGroup, constract){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BTreeKeyFactory factory;

	Btree btree(baseDir, &name, &cacheManager, &factory);

	BtreeConfig config;
	btree.create(&config);
}

TEST(TestBTreeGroup, open){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BTreeKeyFactory factory;

	Btree btree(baseDir, &name, &cacheManager, &factory);

	BtreeConfig config;
	btree.create(&config);

	BtreeOpenConfig opconf;
	btree.open(&opconf);

	btree.close();

}
