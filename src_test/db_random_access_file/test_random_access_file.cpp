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

#include "random_access_file/MMapSegment.h"

using namespace alinous;


TEST_GROUP(RAFTestGroup) {
	TestSetup testenv;

	TEST_SETUP() {
		printf("TEST_SETUP();");fflush(stdout);
		testenv.setup();
	}
	TEST_TEARDOWN() {
		printf("TEST_TEARDOWN();");fflush(stdout);
		testenv.teardown();
	}
};

TEST(RAFTestGroup, construct){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString mode(L"wr");

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	RandomAccessFile file(outFile, nullptr);
	file.open();
}

TEST(RAFTestGroup, openError){
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

TEST(RAFTestGroup, setLengthError01){
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

TEST(RAFTestGroup, fileSetupWriteError01){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

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

TEST(RAFTestGroup, fileSetupWriteError02){
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


TEST(RAFTestGroup, fileRead){
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
	file.read(fpos, buff, 8);

	delete [] buff;
}

TEST(RAFTestGroup, fileReadAndClose){
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
	file.read(fpos, buff, 8);

	delete [] buff;

	file.close();
	CHECK(diskCache.size() == 0)

	file.open();
}

TEST(RAFTestGroup, fileReadError){
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

	errmgr->activatePoint(L"MMapSegment::loadData::01", L"Os::seekFile", 1);

	Exception* exp = nullptr;
	try{
		file.read(fpos, buff, 8);
	}catch(Exception* e){
		exp = e;
	}
	CHECK(dynamic_cast<FileIOException*>(exp) != nullptr)
	delete exp;

	delete [] buff;
}

TEST(RAFTestGroup, fileReadError2){
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

	errmgr->activatePoint(L"MMapSegment::loadData::02", L"Os::readFile", 1);

	Exception* exp = nullptr;
	try{
		file.read(fpos, buff, 8);
	}catch(Exception* e){
		exp = e;
	}
	CHECK(dynamic_cast<FileIOException*>(exp) != nullptr)
	delete exp;


	delete [] buff;
}

TEST(RAFTestGroup, fileWrite){
	printf("fileWrite starts\n");fflush(stdout);

	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	printf("init debug info\n");fflush(stdout);

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(1);
	RandomAccessFile file(outFile, &diskCache);

	printf("before open\n");fflush(stdout);

	file.open();

	printf("after open\n");fflush(stdout);

	int buffSize = 8;
	uint64_t fpos = 12;

	char* buff = new char[buffSize];
	StackArrayRelease<char> r_buff(buff);

	file.write(fpos, buff, buffSize);

	printf("after write\n");fflush(stdout);

}

/*
TEST(RAFTestGroup, getSegment){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(1);
	RandomAccessFile file(outFile, &diskCache);

	file.open();

	uint64_t fpos = 12;
	MMapSegment* seg = file.getSegment(fpos);
	seg->decRefCount();

	fpos = Os::getSystemPageSize() * 64;
	Exception* exp = nullptr;
	try{
		seg = file.getSegment(fpos);
	}catch(Exception* e){
		exp = e;
	}
	CHECK(dynamic_cast<FileIOException*>(exp) != nullptr)
	delete exp;
}
*/
