/*
 * test_thread_random_access_file.cpp
 *
 *  Created on: 2018/05/01
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"
#include "test_utils/TestSetup.h"

#include "random_access_file/RandomAccessFile.h"
#include "random_access_file/DiskCacheManager.h"
#include "random_access_file/MMapSegment.h"
#include "base_io_stream/exceptions.h"

#include "base_thread/AbstractThreadRunner.h"

#include "osenv/funcs.h"

using namespace alinous;


TEST_GROUP(RandomAccessFileThreadTestGroup) {
	TestSetup testenv;

	TEST_SETUP() {
		testenv.setup();
	}
	TEST_TEARDOWN() {
		testenv.teardown();
	}
};

class TestSegRuuer : public AbstractThreadRunner {
public:
	TestSegRuuer(const UnicodeString* name, RandomAccessFile* file, TestBreak* breakpoint, uint64_t fpos): AbstractThreadRunner(name),
				file(file), breakpoint(breakpoint), fpos(fpos) {}
	virtual ~TestSegRuuer(){}

	virtual void process() noexcept{
		breakpoint->breakpoint(1);

		MMapSegment* seg = file->getSegment(fpos);

		breakpoint->breakpoint(2);

		Os::usleep(30 * 1000);

		seg->decRefCount();
	}
private:
	RandomAccessFile* file;
	TestBreak* breakpoint;
	uint64_t fpos;
};



TEST(RandomAccessFileThreadTestGroup, getSegmentCacheOut01){
	File projectFolder = this->testenv.testCaseDir();
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	DiskCacheManager diskCache(1);
	RandomAccessFile file(outFile, &diskCache);

	file.open(true);

	uint64_t segsize = Os::getSystemPageSize() * 4;
	uint64_t newLength = segsize * 3;
	file.setLength(newLength);

	// thread test
	UnicodeString str01(L"test01");
	UnicodeString str02(L"test02");
	TestBreak break01;
	TestBreak break02;
	TestSegRuuer* runner01 = new TestSegRuuer(&str01, &file, &break01, 10);
	TestSegRuuer* runner02 = new TestSegRuuer(&str02, &file, &break02, segsize * 2 + 1);

	StackRelease<TestSegRuuer> r_runner01(runner01);
	StackRelease<TestSegRuuer> r_runner02(runner02);
	runner01->start();
	runner02->start();

	break01.resume(1);
	while(break01.current() != 2){
		Os::usleep(1000);
	}

	break02.resume(1);

	break01.resume(2);
	break02.resume(2);

	runner01->join();
	runner02->join();
}


