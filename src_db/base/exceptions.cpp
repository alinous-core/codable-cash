/*
 * exceptions.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#include <base/exceptions.h>

namespace alinous {

const wchar_t* NumberFormatException::defaultMessage = L"Buffer is under flown";

NumberFormatException::NumberFormatException() noexcept : Exception() {
	this->message = new UnicodeString(defaultMessage);
}
NumberFormatException::NumberFormatException(Exception* cause) noexcept : Exception(cause) {
	this->message = new UnicodeString(defaultMessage);
}
NumberFormatException::NumberFormatException(UnicodeString* message) noexcept : Exception(message) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
NumberFormatException::NumberFormatException(UnicodeString* message, Exception* cause) noexcept : Exception(message, cause) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
NumberFormatException::~NumberFormatException() {
}

} /* namespace alinous */
