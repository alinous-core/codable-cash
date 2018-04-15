/*
 * test_charsets.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"

#include "charsets/CharsetManager.h"
#include "base/UnicodeString.h"

using namespace alinous;


TEST_GROUP(CharsetTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(CharsetTestGroup, construct){
	CharsetManager* mgr = CharsetManager::getInstance();
	CharsetManager::closeInstance();
}

TEST(CharsetTestGroup, getConverter){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);

	CharsetManager::closeInstance();
}

