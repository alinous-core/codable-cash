/*
 * ErrorActivationPoint.cpp
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#include "debug/ErrorActivationPoint.h"
#include "debug/ErrorOccurrence.h"

#include "base/UnicodeString.h"


namespace alinous {

ErrorActivationPoint::ErrorActivationPoint(const wchar_t* name, ErrorOccurrence* error) {
	this->name = new UnicodeString(name);
	this->error = error;
}

ErrorActivationPoint::~ErrorActivationPoint() {
	delete name;
}

} /* namespace alinous */
