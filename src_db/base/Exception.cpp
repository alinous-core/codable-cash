/*
 * Exception.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base/Exception.h"
#include "base/UnicodeString.h"

namespace alinous {

Exception::Exception(const char* srcfile, int srcline) noexcept {
	this->srcfile = srcfile;
	this->srcline = srcline;
	this->cause = nullptr;
	this->message = nullptr;
}

Exception::Exception(Exception* cause, const char* srcfile, int srcline) noexcept {
	this->srcfile = srcfile;
	this->srcline = srcline;
	this->cause = cause;
	this->message = nullptr;
}
Exception::Exception(UnicodeString* message, const char* srcfile, int srcline) noexcept {
	this->srcfile = srcfile;
	this->srcline = srcline;
	this->cause = nullptr;
	this->message = message;
}
Exception::Exception(UnicodeString* message, Exception* cause, const char* srcfile, int srcline) noexcept {
	this->srcfile = srcfile;
	this->srcline = srcline;
	this->cause = cause;
	this->message = message;
}

Exception::~Exception() {
	if(this->message != nullptr){
		delete this->message;
	}
	if(this->cause != nullptr){
		delete this->cause;
	}
}

} /* namespace alinous */
