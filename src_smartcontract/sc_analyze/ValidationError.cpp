/*
 * ValidationError.cpp
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#include "sc_analyze/ValidationError.h"

#include "base/UnicodeString.h"

namespace alinous {

ValidationError::ValidationError(int type, CodeElement* element, const UnicodeString* msg) {
	this->type = type;
	this->element = element;
	this->message = new UnicodeString(*msg);
}

ValidationError::~ValidationError() {
	this->element = nullptr;
	delete this->message;
}

} /* namespace alinous */
