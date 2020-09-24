/*
 * test_thread_random_access_file.cpp
 *
 *  Created on: 2018/05/01
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "random_access_file/RandomAccessFile.h"
#include "random_access_file/DiskCacheManager.h"
#include "random_access_file/MMapSegment.h"
#include "base_io_stream/exceptions.h"

#include "base_thread/AbstractThreadRunner.h"

#include "osenv/funcs.h"

#include "test_utils/TestBreak.h"
using namespace alinous;


TEST_GROUP(RAFCacheOut) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

class TestSegRuuer : public AbstractThreadRunner {
public:
	TestSegRuuer(const UnicodeString* name, RandomAccessFile* file, TestBreak* breakpoint, uint64_t fpos, int no): AbstractThreadRunner(name),
				file(file), breakpoint(breakpoint), fpos(fpos), no(no){
		this->seg = nullptr;
	}
	virtual ~TestSegRuuer(){}

	virtual void process() noexcept{
		breakpoint->breakpoint(1);

		seg = file->getSegment(fpos);

		breakpoint->breakpoint(2);

		seg->decRefCount();
	}

private:
	RandomAccessFile* file;
	TestBreak* breakpoint;
	uint64_t fpos;
	int no;
	MMapSegment* seg;
};


static void testOnce(File projectFolder){
	ErrorPointManager* errmgr = ErrorPointManager::getInstance();

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	if(outFile->exists()){
		outFile->deleteFile();
	}

	DiskCacheManager diskCache(16525);
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
	TestSegRuuer* runner01 = new TestSegRuuer(&str01, &file, &break01, 10, 1);
	TestSegRuuer* runner02 = new TestSegRuuer(&str02, &file, &break02, segsize * 2 + 1, 2);

	StackRelease<TestSegRuuer> r_runner01(runner01);
	StackRelease<TestSegRuuer> r_runner02(runner02);
	runner01->start();
	runner02->start();

	break01.resume(1);

	// wait for first thread got segment
	while(break01.current() != 2){
		Os::usleep(100);
	}

	break02.resume(1);

	// before resume first one, wait for second thread is waiting
	Os::usleep(1000);

	break01.resume(2);
	break02.resume(2);

	runner01->join();
	runner02->join();
}


TEST(RAFCacheOut, getSegmentCacheOut01){
	File projectFolder = this->env->testCaseDir();

	for(int i = 0; i != 10; ++i){
		testOnce(projectFolder);
	}
}


