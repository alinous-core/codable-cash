/*
 * test_test.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"


using namespace alinous;

TEST_GROUP(test_test){
	TEST_SETUP(){
		this->env->setup();
	}
	TEST_TEARDOWN(){
		this->env->teardown();
	}
};

TEST(test_test, test01){
	File projectFolder = this->env->testCaseDir();

	UnicodeString* pathstr = projectFolder.getAbsolutePath();
	StackRelease<UnicodeString> r_pathstr(pathstr);

	UnicodeString ends(L"test_test/test01");
	CHECK(pathstr->endsWith(&ends));

	int val = 10;
	CHECK(val == 10);
}
/*
TEST(test_test, test02){
	int val = 10;
	CHECK(val != 10);
}
*/


