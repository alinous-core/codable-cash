/*
 * Check.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "test_utils/Check.h"
#include "base/UnicodeString.h"

#include "test_utils/TestCase.h"


namespace alinous {

ThreadKeyRegistory* Check::getThreadKeyRegistory() {
	static ThreadKeyRegistory reg;
	return &reg;
}

ThreadKeyRegistory::ThreadKeyRegistory() {
}

ThreadKeyRegistory::~ThreadKeyRegistory() {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		ThreadKeySet* key = list.get(i);
		Os::threadKeyDelete(key->key);

		delete key;
	}
}

void ThreadKeyRegistory::registerTestCase(TestCase* testCase) {
	ThreadKeySet* pkey = getKey();

	if(pkey == nullptr){
		pkey = new ThreadKeySet;
		pkey->id = Os::getCurrentThreadId();
		int ret = Os::threadKeyCreate(&pkey->key);
		this->list.addElement(pkey);
	}

	Os::threadSetSpecific(pkey->key, testCase);
}


ThreadKeySet* ThreadKeyRegistory::getKey() {
	THREAD_ID tid = Os::getCurrentThreadId();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		ThreadKeySet* key = list.get(i);

		if(key->id == tid){
			return key;
		}
	}

	return nullptr;
}


alinous::Check::Check(TestCase* testCase, const char* file, int line) {
	this->file = new UnicodeString(file);
	this->line = line;
	this->ok = true;
	this->testCase = testCase;
}

alinous::Check::~Check() {
	delete this->file;
}

void alinous::Check::checkCondition(bool condition) noexcept {
	this->ok = condition;
	if(!condition){
		this->testCase->setFailed();
	}
}

bool Check::isOk() const noexcept{
	return this->ok;
}

Check* __mcAddcheck(alinous::Check* chk){
	THREAD_ID tid = Os::getCurrentThreadId();

	ThreadKeySet* ketset = Check::getThreadKeyRegistory()->getKey();

	void* ptr = Os::threadGetSpecific(ketset->key);
	TestCase* testCase = static_cast<TestCase*>(ptr);
	testCase->addCheck(chk);

	return chk;
}

} /* namespace alinous */

