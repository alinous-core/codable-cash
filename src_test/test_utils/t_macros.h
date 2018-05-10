/*
 * macros.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef DEBUG_T_MACROS_H_
#define DEBUG_T_MACROS_H_

#include "test_utils/TestGroupActions.h"
#include "test_utils/TestExecutor.h"
#include "test_utils/TestGroup.h"
#include "test_utils/TestCase.h"
#include "test_utils/Check.h"
#include "test_utils/TestEnv.h"

#include "base_io/File.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#define _STR_L(str) L##str
#define STR_L(str) _STR_L(#str)


#define TEST_GROUP(grp) \
class GRP_##grp : public TestGroup { \
public: \
	GRP_##grp(const wchar_t* groupName, const char* file, int line) : TestGroup(groupName, file, line){} \
	virtual ~GRP_##grp(){} \
} grp_##grp##_inst(STR_L(grp), __FILE__, __LINE__); \
struct TestGroupSetup_##grp : public TestGroupActions

#define TEST_SETUP virtual void setup()
#define TEST_TEARDOWN virtual void teardown()

#define TEST(grp, testName) \
class TestCase_##grp##_##testName : TestCase { \
public: \
	TestCase_##grp##_##testName(TestGroup* group, const wchar_t* name, TestGroupActions* setup, const char* file, int line) : TestCase(group, name, setup, file, line){} \
	virtual ~TestCase_##grp##_##testName(){} \
	virtual void testBody(); \
} grp##_##testName##_inst(&grp_test_test_inst, STR_L(testName), new TestGroupSetup_##grp(), __FILE__, __LINE__); \
void TestCase_##grp##_##testName::testBody()


#define CHECK(cnd) addCheck(new Check(env->getTestCase(), __FILE__, __LINE__))->checkCondition(cnd);

#endif /* DEBUG_T_MACROS_H_ */
