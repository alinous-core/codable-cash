/*
 * test_stack_release.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

using namespace alinous;



TEST_GROUP(StackReleaseTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};
TEST(StackReleaseTestGroup, construct){
	UnicodeString* str = new UnicodeString(L"test");
	StackRelease<UnicodeString>* __release = new StackRelease<UnicodeString>(str);

	delete __release;
}


