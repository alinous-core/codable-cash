/*
 * ErrorOccurrence.cpp
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#include "debug/ErrorOccurrence.h"

#include "base/UnicodeString.h"

namespace alinous {

ErrorOccurrence::ErrorOccurrence(const wchar_t* name, int errorCount) : errorCount(errorCount), count(0) {
	this->name = new UnicodeString(name);
}

ErrorOccurrence::~ErrorOccurrence() {
	delete name;
}

bool ErrorOccurrence::hit(const wchar_t* name) noexcept {
	UnicodeString nameStr(name);

	if(this->name->equals(&nameStr)){
		this->count++;
	}

	return this->errorCount == this->count;
}

} /* namespace alinous */
