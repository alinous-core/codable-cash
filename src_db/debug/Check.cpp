/*
 * Check.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "debug/Check.h"
#include "base/UnicodeString.h"

namespace alinous {

alinous::Check::Check(const char* file, int line) {
	this->file = new UnicodeString(file);
	this->line = line;
	this->ok = true;
}

alinous::Check::~Check() {
}

void alinous::Check::checkCondition(bool condition) noexcept {
	this->ok = condition;
}



} /* namespace alinous */
