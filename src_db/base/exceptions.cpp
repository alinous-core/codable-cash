/*
 * exceptions.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base/exceptions.h"
#include "UnicodeString.h"

namespace alinous {

const wchar_t* NumberFormatException::defaultMessage = L"Buffer is under flown";

NumberFormatException::NumberFormatException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
NumberFormatException::NumberFormatException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
NumberFormatException::NumberFormatException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
NumberFormatException::NumberFormatException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
NumberFormatException::~NumberFormatException() {
}


const wchar_t* IllegalArgumentException::defaultMessage = L"Illegal argument";

IllegalArgumentException::IllegalArgumentException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
IllegalArgumentException::IllegalArgumentException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
IllegalArgumentException::IllegalArgumentException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
IllegalArgumentException::IllegalArgumentException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
IllegalArgumentException::~IllegalArgumentException() {
}

} /* namespace alinous */
