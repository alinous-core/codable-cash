/*
 * test_random_access_file.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "random_access_file/RandomAccessFile.h"
#include "random_access_file/DiskCacheManager.h"
#include "base_io_stream/exceptions.h"

#include "random_access_file/MMapSegment.h"

using namespace alinous;


TEST_GROUP(RAFTestGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};
/*
TEST(RAFTestGroup, segSize){
	uint64_t segSize = Os::getSystemPageSize();
	printf("%ld\n", segSize);
}
*/
TEST(RAFTestGroup, construct){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString mode(L"wr");

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	RandomAccessFile file(outFile, nullptr);
	file.open();
}

TEST(RAFTestGroup, openError){
	File projectFolder = this->env->testCaseDir();
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
	File projectFolder = this->env->testCaseDir();
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
	File projectFolder = this->env->testCaseDir();
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
	File projectFolder = this->env->testCaseDir();
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
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
	RandomAccessFile file(outFile, &diskCache);

	file.open();

	char* buff = new char[8];
	uint64_t fpos = 12;
	file.read(fpos, buff, 8);
	file.read(fpos, buff, 8);

	delete [] buff;
}

TEST(RAFTestGroup, fileReadAndClose){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
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
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
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
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
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
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();


	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
	RandomAccessFile file(outFile, &diskCache);

	file.open();

	int buffSize = 8;
	uint64_t fpos = 12;

	char* buff = new char[buffSize]{};
	StackArrayRelease<char> r_buff(buff);

	file.write(fpos, buff, buffSize);
}

TEST(RAFTestGroup, fileWriteSync){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();


	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
	RandomAccessFile file(outFile, &diskCache);

	file.open();

	int buffSize = 8;
	uint64_t fpos = 12;

	char* buff = new char[buffSize]{};
	StackArrayRelease<char> r_buff(buff);

	file.write(fpos, buff, buffSize);

	file.sync(true);
}

TEST(RAFTestGroup, fileWriteSyncError){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();


	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
	RandomAccessFile file(outFile, &diskCache);

	file.open();

	int buffSize = 8;
	uint64_t fpos = 12;

	char* buff = new char[buffSize]{};
	StackArrayRelease<char> r_buff(buff);

	file.write(fpos, buff, buffSize);

	errmgr->activatePoint(L"MMapSegment::writeBack", L"Os::write2File", 1);

	Exception* exp = nullptr;
	try{
		file.sync(true);
	}catch(Exception* e){
		exp = e;
		file.close();
	}
	CHECK(dynamic_cast<FileIOException*>(exp) != nullptr)
	delete exp;

}

TEST(RAFTestGroup, fileWriteSyncError02){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();


	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
	RandomAccessFile file(outFile, &diskCache);

	file.open();

	int buffSize = 8;
	uint64_t fpos = 12;

	char* buff = new char[buffSize]{};
	StackArrayRelease<char> r_buff(buff);

	file.write(fpos, buff, buffSize);

	errmgr->activatePoint(L"RandomAccessFile::sync", L"Os::syncFile", 1);

	Exception* exp = nullptr;
	try{
		file.sync(true);
	}catch(Exception* e){
		exp = e;
		file.close();
	}
	CHECK(dynamic_cast<FileIOException*>(exp) != nullptr)
	delete exp;

}


TEST(RAFTestGroup, getSegment){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
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

TEST(RAFTestGroup, constructWithPagesize){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
	RandomAccessFile file(outFile, &diskCache, 256);

	file.open();
}

TEST(RAFTestGroup, pagesizeChange){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	//printf("before DiskCacheManager\n");::fflush(stdout);

	DiskCacheManager diskCache(16525);
	RandomAccessFile file(outFile, &diskCache, 256); // page size * 4 = 1024

	file.open();

	char* buff = new char[8];
	uint64_t fpos = 12;
	file.read(fpos, buff, 8);
	file.read(fpos, buff, 8);

	delete [] buff;

	MMapSegment* seg = file.getSegment(fpos);
	seg->setDirty(true);
	seg->decRefCount();

	file.setLength(1024 + 64);

	file.close();
}

TEST(RAFTestGroup, readWrite){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	const char* str = "Hello World!!\n";
	{
		DiskCacheManager diskCache(16525);
		RandomAccessFile file(outFile, &diskCache, 256);
		file.open();


		file.write(0, str, 15);

		char buff[14]{};
		file.read(0, buff, 15);

		file.sync(true);

		file.close();
	}

	{
		DiskCacheManager diskCache(16525);
		RandomAccessFile file(outFile, &diskCache, 256);
		file.open();
		char buff[15]{};
		file.read(0, buff, 15);

		file.close();

		int result = Mem::strcmp(str, buff);
		CHECK(result == 0)
	}
}

TEST(RAFTestGroup, readWrite02){
	File projectFolder = this->env->testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	const char* str = "Hello World!!\n";
	{
		DiskCacheManager diskCache(16525);
		RandomAccessFile file(outFile, &diskCache, 256);
		file.open();

		file.setLength(256 * 4 * 2);

		file.write(256 * 4 - 6, str, 15);

		char buff[14]{};
		file.read(0, buff, 15);

		file.sync(true);

		file.close();
	}

	{
		DiskCacheManager diskCache(16525);
		RandomAccessFile file(outFile, &diskCache, 256);
		file.open();
		char buff[15]{};
		file.read(256 * 4 - 6, buff, 15);

		file.close();

		int result = Mem::strcmp(str, buff);
		CHECK(result == 0)
	}
}

TEST(RAFTestGroup, notExists){
	File projectFolder = this->env->testCaseDir();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(16525);
	RandomAccessFile file(outFile, &diskCache, 256);
	bool ex = file.exists();
	CHECK(!ex)
}


