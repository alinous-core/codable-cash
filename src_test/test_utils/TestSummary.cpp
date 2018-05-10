/*
 * TestSummary.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "test_utils/TestSummary.h"
#include "test_utils/TestCase.h"
#include "test_utils/TestGroup.h"
#include "test_utils/Check.h"

#include "base/UnicodeString.h"

namespace alinous {

TestSummary::TestSummary() noexcept {
	this->totalTests = 0;
	this->successedTest = 0;
	this->failedTest = 0;
	this->successedcheck = 0;
	this->failedcheck = 0;

	this->failedTests = new HashMap<UnicodeString, ArrayList<TestCase>>();
}

TestSummary::~TestSummary() noexcept {
	Iterator<UnicodeString>* it = this->failedTests->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		ArrayList<TestCase>* listptr = this->failedTests->get(key);

		delete listptr;
	}
	delete it;

	delete this->failedTests;
}

void alinous::TestSummary::analyze(TestCase* testCase) noexcept {
	const TestGroup* grp = testCase->getGroup();
	UnicodeString* grpName = grp->getName();

	this->totalTests++;

	if(!testCase->isDone()){
		return;
	}

	if(testCase->isFailed()){
		this->failedTest++;
		ArrayList<TestCase>* filedlistList = getGroupCaseList(grpName);
		filedlistList->addElement(testCase);
	}
	else{
		this->successedTest++;
	}

	ArrayList<Check>* checkList = testCase->getChecks();
	analyzeChecks(checkList);
}

void TestSummary::echoSummary() const noexcept {
	float percent = ((float)this->successedTest / (float)this->totalTests) * 100;

	printf("  %.2lf%% success (Total : %d, Success %d, Failed %d)\n", percent, this->totalTests, this->successedTest, this->failedTest);
	printf("  Checks(success : %d, failed :%d)\n", this->successedcheck, this->failedcheck);

	if(this->failedTest != 0){
		printf("Failure Report\n");
	}
}

void TestSummary::analyzeChecks(ArrayList<Check>* checkList) noexcept{
	int maxLoop = checkList->size();
	for(int i = 0; i != maxLoop; ++i){
		Check* check = checkList->get(i);

		if(check->isOk()){
			this->successedcheck++;
		}else{
			this->failedcheck++;
		}
	}
}

ArrayList<TestCase>* TestSummary::getGroupCaseList(const UnicodeString* grp) noexcept {
	ArrayList<TestCase>* list = this->failedTests->get(grp);
	if(list == nullptr){
		list = new ArrayList<TestCase>();
		this->failedTests->put(grp, list);
	}
	return list;
}



} /* namespace alinous */


