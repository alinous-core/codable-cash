/*
 * test_filestore.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "db_exceptions.h"

#include "random_access_file/DiskCacheManager.h"
#include "base_io/File.h"
#include "base/StackRelease.h"

#include "filestore/FileStore.h"

using namespace alinous;

TEST_GROUP(TestFileStoreGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestFileStoreGroup, exceptions){
	testException<FileStorageException>();
}

TEST(TestFileStoreGroup, construct){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	FileStore store(baseDirStr, &name, &cacheManager);
}

TEST(TestFileStoreGroup, createNew){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file01");
	FileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(true, 1024);
}


TEST(TestFileStoreGroup, createNewDelete){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file02");
	FileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(true, 1024);

	store.createStore(true, 1024);

}

TEST(TestFileStoreGroup, openClose){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())

	DiskCacheManager cacheManager;
	UnicodeString name(L"file02");
	FileStore store(baseDirStr, &name, &cacheManager);

	store.createStore(true, 1024);

	store.open(true);

	CHECK(store.isOpened())

}
