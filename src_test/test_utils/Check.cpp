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

} /* namespace alinous */
