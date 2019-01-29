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

#include "base_io/ByteBuffer.h"

#include "filestore_block/BlockFileStore.h"
#include "filestore_block/BlockHandle.h"
#include "filestore_block/exceptions.h"

#include "random_access_file/RandomAccessFile.h"

#include "db_exceptions.h"

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
	testException<BinaryFormatException>();
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
	errmgr->activatePoint(L"BlockFileStore::createStore", L"RandomAccessFile::write", 1);


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

static const char* makeTestData(int start, int length) {
	char* ptr = new char[length];

	for(int i = 0; i != length; ++i){
		char ch = start % 128;
		start++;

		ptr[i] = ch;
	}
	return ptr;
}

static bool checkTestData(int start, const char* data, int length) {
	for(int i = 0; i != length; ++i){
		char ch = start % 128;
		start++;

		if(data[i] != ch){
			return false;
		}
	}
	return true;
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

	{
		BlockHandle* handle = store.alloc(10);

		const char* data = makeTestData(3, 10);
		StackArrayRelease<const char> _st_data(data);

		handle->write(data, 10);

		uint64_t fpos = handle->getFpos();
		delete handle;

		handle = store.get(fpos);

		CHECK(handle->size() == 10)

		ByteBuffer* buff = handle->getBuffer();

		bool checkTest = checkTestData(3, (const char*)buff->array(), 10);
		CHECK(checkTest)

		delete handle;
	}

	store.close();
}

TEST(TestBlockFileStoreGroup, alloc02){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 256);
	store.open(false);

	{
		BlockHandle* handle = store.alloc(520);

		int datasize = 500;
		const char* data = makeTestData(3, datasize);
		StackArrayRelease<const char> _st_data(data);

		handle->write(data, datasize);
		uint64_t fpos = handle->getFpos();

		delete handle;

		handle = store.get(fpos);
		CHECK(handle->size() == datasize)

		ByteBuffer* buff = handle->getBuffer();
		bool checkTest = checkTestData(3, (const char*)buff->array(), 10);
		CHECK(checkTest)

		delete handle;
	}
	store.close();
}

TEST(TestBlockFileStoreGroup, alloc03){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 256);
	store.open(false);

	{
		BlockHandle* handle = store.alloc(100);

		int datasize = 500;
		const char* data = makeTestData(3, datasize);
		StackArrayRelease<const char> _st_data(data);

		handle->write(data, datasize);
		uint64_t fpos = handle->getFpos();

		delete handle;

		handle = store.get(fpos);
		CHECK(handle->size() == datasize)

		ByteBuffer* buff = handle->getBuffer();
		bool checkTest = checkTestData(3, (const char*)buff->array(), datasize);
		CHECK(checkTest)

		delete handle;
	}

	store.close();
}

TEST(TestBlockFileStoreGroup, alloc04){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 256);
	store.open(false);

	{
		BlockHandle* handle = store.alloc(1000);

		int datasize = 300;
		const char* data = makeTestData(3, datasize);
		StackArrayRelease<const char> _st_data(data);

		handle->write(data, datasize);
		uint64_t fpos = handle->getFpos();

		delete handle;

		handle = store.get(fpos);
		CHECK(handle->size() == datasize)

		ByteBuffer* buff = handle->getBuffer();
		bool checkTest = checkTestData(3, (const char*)buff->array(), datasize);
		CHECK(checkTest)

		delete handle;

	}

	store.close();
}

TEST(TestBlockFileStoreGroup, allocError){
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	BlockFileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(false, 256);
	store.open(false);

	//
	errmgr->activatePoint(L"BlockFileStore::alloc", L"RandomAccessFile::write", 1);

	Exception* exp = nullptr;
	try {
		store.alloc(100);
	} catch (Exception* e) {
		exp = e;
	}

	delete exp;
}

