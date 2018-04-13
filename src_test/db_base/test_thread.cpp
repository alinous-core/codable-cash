/*
 * test_thread.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */



#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"
#include "base/SysMutex.h"

using namespace alinous;


TEST_GROUP(SysMutexTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(SysMutexTestGroup, test01){
	SysMutex mutex;

	mutex.lock();

	mutex.unlock();
}
