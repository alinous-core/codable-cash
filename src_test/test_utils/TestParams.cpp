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
}

TestParams::~TestParams() noexcept {
	this->execGroups.deleteElements();
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

} /* namespace alinous */

