/*
 * exceptions.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#include <base/exceptions.h>
#include "UnicodeString.h"

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


const wchar_t* IllegalArgumentException::defaultMessage = L"Illegal argument";

IllegalArgumentException::IllegalArgumentException() noexcept : Exception() {
	this->message = new UnicodeString(defaultMessage);
}
IllegalArgumentException::IllegalArgumentException(Exception* cause) noexcept : Exception(cause) {
	this->message = new UnicodeString(defaultMessage);
}
IllegalArgumentException::IllegalArgumentException(UnicodeString* message) noexcept : Exception(message) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
IllegalArgumentException::IllegalArgumentException(UnicodeString* message, Exception* cause) noexcept : Exception(message, cause) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
IllegalArgumentException::~IllegalArgumentException() {
}

} /* namespace alinous */
