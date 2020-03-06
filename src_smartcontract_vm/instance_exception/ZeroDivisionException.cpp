/*
 * ZeroDivisionException.cpp
 *
 *  Created on: 2020/03/06
 *      Author: iizuka
 */

#include "instance_exception/ZeroDivisionException.h"

#include "base/UnicodeString.h"


namespace alinous {

const wchar_t* ZeroDivisionException::defaultMessage = L"Can not div/mod by zero. ";

ZeroDivisionException::ZeroDivisionException(const char* srcfile, int srcline) noexcept : AbstructProgramException(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
ZeroDivisionException::ZeroDivisionException(Exception* cause, const char* srcfile, int srcline) noexcept : AbstructProgramException(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
ZeroDivisionException::ZeroDivisionException(const wchar_t* message, const char* srcfile, int srcline) noexcept : AbstructProgramException(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
ZeroDivisionException::ZeroDivisionException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : AbstructProgramException(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
ZeroDivisionException::~ZeroDivisionException() {
}

} /* namespace alinous */
