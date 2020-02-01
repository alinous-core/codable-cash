/*
 * TestParams.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "test_utils/TestParams.h"
#include "osenv/funcs.h"
#include "osenv/memory.h"

namespace alinous {

TestParams::TestParams() noexcept {
	this->v = false;
	this->testName = nullptr;
}

TestParams::~TestParams() noexcept {
	this->execGroups.deleteElements();
	delete this->testName;
}

void TestParams::init(int ac, char** av) {
	int length = ac;
	for(int i = 1; i != length; ++i){
		char* value = av[i];

		if(Mem::strcmp(value, "-v") == 0){
			this->v = true;
		}
		else if(Mem::strcmp(value, "-g") == 0){
			char* grpcstr = nextParam(&i, av, length);
			this->execGroups.addElement(new UnicodeString(grpcstr));
		}
		else if(Mem::strcmp(value, "-t") == 0){
			char* grpcstr = nextParam(&i, av, length);
			this->testName = new UnicodeString(grpcstr);
		}
		else{
			throw new TestParamsException();
		}
	}
}

char* TestParams::nextParam(int* i, char** av, int length) {
	(*i)++;
	if(*i >= length){
		throw new TestParamsException();
	}

	return av[*i];
}

bool TestParams::skipGroup(const UnicodeString* grp) const noexcept {
	int size = this->execGroups.size();
	if(size == 0){
		return false;
	}

	for(int i = 0; i != size; ++i){
		UnicodeString* value = this->execGroups.get(i);
		if(value->equals(grp)){
			return false;
		}
	}
	return true;
}


bool TestParams::skipTest(const UnicodeString* t) const noexcept {
	if(this->testName == nullptr){
		return false;
	}

	if(t->equals(this->testName)){
		return false;
	}

	return true;
}

} /* namespace alinous */
