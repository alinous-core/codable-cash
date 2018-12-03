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
#include "filestore_block/BlockHandle.h"
#include "filestore_block/exceptions.h"

#include "random_access_file/RandomAccessFile.h"

using namespace alinous;

TEST_GROUP(TestBlockFileStoreGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestBlockFileStoreGroup, exceptions){
	testException<BlockFileStorageException>();
}

TEST(TestBlockFileStoreGroup, construct){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);
}

TEST(TestBlockFileStoreGroup, createStore){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 1024);
}

TEST(TestBlockFileStoreGroup, createStoreFailure){
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();
	errmgr->activatePoint(L"BlockFileStore::createStore", L"Os::syncFile", 1);


	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	Exception* exp = nullptr;
	try{
		store.createStore(false, 1024);
	}catch(Exception* e){
		exp = e;
	}

	CHECK(exp != nullptr)
	delete exp;
}

TEST(TestBlockFileStoreGroup, openStore){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 1024);

	store.open(false);

	CHECK(store.isOpened())
}

TEST(TestBlockFileStoreGroup, openStoreError){
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();
	errmgr->activatePoint(L"BlockFileStore::open", L"Os::seekFile", 1);

	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 1024);

	Exception* exp = nullptr;
	try{
		store.open(false);
	}catch(Exception* e){
		exp = e;
	}

	CHECK(exp != nullptr)
	delete exp;
}

TEST(TestBlockFileStoreGroup, openStoreError2){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 1024);

	{
		_ST(UnicodeString, headerfilename, new UnicodeString(name))
		headerfilename->append(L"-header.bin");
		_ST(File, storeHeaderFile, baseDir->get(headerfilename))
		RandomAccessFile* headerFile = new RandomAccessFile(storeHeaderFile, &cacheManager);

		headerFile->open(false);

		uint64_t zero = 0;
		headerFile->write(0, (char*)&zero, sizeof(uint64_t));
		headerFile->sync(true);
		headerFile->close();
		delete headerFile;
	}

	Exception* exp = nullptr;
	try{
		store.open(false);
	}catch(Exception* e){
		exp = e;
	}

	CHECK(exp != nullptr)
	delete exp;
}

TEST(TestBlockFileStoreGroup, alloc01){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 1024);

	store.open(false);

	BlockHandle* handle = store.alloc(10);



	delete handle;

	store.close();

}


