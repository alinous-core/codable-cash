/*
 * exceptions.cpp
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#include "numeric/exceptions.h"
#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* ArithmeticException::defaultMessage = L"FileStorage error. ";

ArithmeticException::ArithmeticException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
ArithmeticException::ArithmeticException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
ArithmeticException::ArithmeticException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
ArithmeticException::ArithmeticException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
ArithmeticException::~ArithmeticException() {
}

} /* namespace alinous */
