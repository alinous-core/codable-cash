/*
 * test_thread.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base_thread/SysThread.h"
#include "base_thread/SysMutex.h"
#include "TestCountRunner.h"

using namespace alinous;


TEST_GROUP(SysMutexTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(SysMutexTestGroup, run){
	TestCountRunner runner;

	runner.start();

	SysThread* pth = SysThread::getCurrentThread();
	StackRelease<SysThread> r_pth(pth);

	CHECK(!pth->equals(runner.getThread()));

	runner.join();
}

TEST(SysMutexTestGroup, runName){
	UnicodeString name(L"mythread");
	TestCountRunner runner(&name);

	runner.start();

	runner.join();
}


TEST(SysMutexTestGroup, SysMutex){
	SysMutex mutex;

	mutex.lock();

	mutex.unlock();
}
