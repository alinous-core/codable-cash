/*
 * test_random_access_file.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"
#include "test_utils/TestSetup.h"

#include "random_access_file/RandomAccessFile.h"
#include "random_access_file/DiskCacheManager.h"
#include "base_io_stream/exceptions.h"

using namespace alinous;


TEST_GROUP(RandomAccessFileTestGroup) {
	TestSetup testenv;

	TEST_SETUP() {
		testenv.setup();
	}
	TEST_TEARDOWN() {
		testenv.teardown();
	}
};

TEST(RandomAccessFileTestGroup, construct){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString mode(L"wr");

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	RandomAccessFile file(outFile, nullptr);
	file.open();
}

TEST(RandomAccessFileTestGroup, openError){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString mode(L"wr");

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	errmgr->activatePoint(L"RandomAccessFile::open", L"Os::openFile2ReadWrite", 1);

	RandomAccessFile file(outFile, nullptr);

	Exception* exp;
	try{
		file.open();
	}catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr)
	delete exp;
}

TEST(RandomAccessFileTestGroup, setLengthError01){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString mode(L"wr");

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	RandomAccessFile file(outFile, nullptr);

	Exception* exp;
	try{
		file.setLength(100000);
	}catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr)
	delete exp;
}

TEST(RandomAccessFileTestGroup, fileSetupWriteError01){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString mode(L"wr");

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	errmgr->activatePoint(L"RandomAccessFile::setLength::01", L"Os::write2File", 1);

	RandomAccessFile file(outFile, nullptr);

	Exception* exp;
	try{
		file.open();
	}catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr)
	delete exp;
}

TEST(RandomAccessFileTestGroup, fileSetupWriteError02){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	errmgr->activatePoint(L"RandomAccessFile::setLength::02", L"Os::write2File", 1);

	RandomAccessFile file(outFile, nullptr);

	Exception* exp;
	try{
		file.open();
	}catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr)
	delete exp;
}


TEST(RandomAccessFileTestGroup, fileRead){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(1);
	RandomAccessFile file(outFile, &diskCache);

	file.open();

	char* buff = new char[8];
	uint64_t fpos = 12;
	file.read(fpos, buff, 8);

	delete [] buff;
}

TEST(RandomAccessFileTestGroup, fileReadAndClose){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(1);
	RandomAccessFile file(outFile, &diskCache);

	file.open();

	char* buff = new char[8];
	uint64_t fpos = 12;
	file.read(fpos, buff, 8);

	delete [] buff;

	file.close();
	CHECK(diskCache.size() == 0)

	file.open();
}



