/*
 * exceptions.cpp
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#include "btreekey/exceptions.h"
#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* KeyFormatException::defaultMessage = L"Key format is wrong ";

KeyFormatException::KeyFormatException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
KeyFormatException::KeyFormatException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
KeyFormatException::KeyFormatException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
KeyFormatException::KeyFormatException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
KeyFormatException::~KeyFormatException() {
}

} /* namespace alinous */
