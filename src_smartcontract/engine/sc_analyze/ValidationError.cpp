/*
 * ValidationError.cpp
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#include "engine/sc_analyze/ValidationError.h"

#include "base/UnicodeString.h"

namespace alinous {

ValidationError::ValidationError(int type, int errorCode, CodeElement* element, const UnicodeString* msg, std::initializer_list<const UnicodeString*> params) {
	this->type = type;
	this->errorCode = errorCode;
	this->element = element;
	this->message = new UnicodeString(*msg);

	for(const UnicodeString* const & p : params){
		UnicodeString* str = new UnicodeString(p);
		this->msgParams.addElement(str);
	}
}

ValidationError::~ValidationError() {
	this->element = nullptr;
	delete this->message;
	this->msgParams.deleteElements();
}

int ValidationError::getErrorCode() const noexcept {
	return this->errorCode;
}


} /* namespace alinous */
