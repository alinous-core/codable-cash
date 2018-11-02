/*
 * test_block_filestore.cpp
 *
 *  Created on: 2018/10/10
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"
#include "db_exceptions.h"

#include "random_access_file/DiskCacheManager.h"
#include "base_io/File.h"
#include "base/StackRelease.h"

#include "filestore_block/BlockFileStore.h"

using namespace alinous;

TEST_GROUP(TestBlockFileStoreGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};


TEST(TestBlockFileStoreGroup, construct){
	/*File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);*/
}

TEST(TestBlockFileStoreGroup, createStore){
	/*File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 1024);*/

}


