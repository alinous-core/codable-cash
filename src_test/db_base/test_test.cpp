/*
 * test_test.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "debug/t_macros.h"


using namespace alinous;


class GRP_test_test : public TestGroup {
public:
	GRP_test_test(const wchar_t* groupName, const char* file, int line) : TestGroup(groupName, file, line){}
	virtual ~GRP_test_test(){}
} Test_test_inst(L"Test_test", __FILE__, __LINE__);
struct TestGroupSetup_test_test : public TestGroupActions{
	virtual void setup(){}
	virtual void teardown(){}
};

class TestCase_test_test_test01 : TestCase {
public:
	TestCase_test_test_test01(TestGroup* group, const wchar_t* name, TestGroupActions* setup, const char* file, int line) : TestCase(group, name, setup, file, line){}
	virtual void testBody();
} test01_test_test_inst(&Test_test_inst, L"test01_test", new TestGroupSetup_test_test(), __FILE__, __LINE__);
void TestCase_test_test_test01::testBody(){

}


/*
TEST_GROUP(test_test){

}
*/
/*
class test01_test_test : TestCase {
public:

} test01_test_test_inst;
*/
/*
TEST(test_test, test01){

}
*/

