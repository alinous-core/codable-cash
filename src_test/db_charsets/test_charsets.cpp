/*
 * test_charsets.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"

#include "charsets/CharsetManager.h"

using namespace alinous;


TEST_GROUP(CharsetTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(CharsetTestGroup, test01){
	CharsetManager* mgr = new CharsetManager();
	delete mgr;
}


