/*
 * exceptions.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include <base_io/exceptions.h>
#include "base/Exception.h"
#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* BufferUnderflowException::defaultMessage = L"Buffer is under flown";

BufferUnderflowException::BufferUnderflowException() throw() : Exception() {
	this->message = new UnicodeString(defaultMessage);
}
BufferUnderflowException::BufferUnderflowException(Exception* cause) throw() : Exception(cause) {
	this->message = new UnicodeString(defaultMessage);
}
BufferUnderflowException::BufferUnderflowException(UnicodeString* message) throw() : Exception(message) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferUnderflowException::BufferUnderflowException(UnicodeString* message, Exception* cause) throw() : Exception(message, cause) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferUnderflowException::~BufferUnderflowException() {
}


} /* namespace alinous */
