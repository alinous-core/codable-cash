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

Exception::Exception(const char* srcfile, int srcline) noexcept : cause(nullptr), message(nullptr) {
	this->srcfile = srcfile;
	this->srcline = srcline;
}

Exception::Exception(Exception* cause, const char* srcfile, int srcline) noexcept : srcfile(srcfile), srcline(srcline), cause(cause), message(nullptr) {
}
Exception::Exception(UnicodeString* message, const char* srcfile, int srcline) noexcept: srcfile(srcfile), srcline(srcline), cause(nullptr), message(nullptr) {
}
Exception::Exception(UnicodeString* message, Exception* cause, const char* srcfile, int srcline) noexcept : srcfile(srcfile), srcline(srcline), cause(cause), message(nullptr){

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
