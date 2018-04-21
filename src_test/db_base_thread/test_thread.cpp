/*
 * test_thread.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"
#include "test_utils/TestSetup.h"

#include "base_thread/SysMutex.h"

using namespace alinous;


TEST_GROUP(SysMutexTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {
		TestSetup::clearStatics();
	}
};



TEST(SysMutexTestGroup, SysMutex){
	SysMutex mutex;

	mutex.lock();

	mutex.unlock();
}
