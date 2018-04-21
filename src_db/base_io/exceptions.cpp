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

const wchar_t* BufferUnderflowException::defaultMessage = L"Buffer is under flown. ";

BufferUnderflowException::BufferUnderflowException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
BufferUnderflowException::BufferUnderflowException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
BufferUnderflowException::BufferUnderflowException(UnicodeString* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferUnderflowException::BufferUnderflowException(UnicodeString* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferUnderflowException::~BufferUnderflowException() {
}


const wchar_t* BufferOverflowException::defaultMessage = L"Buffer is under flown. ";

BufferOverflowException::BufferOverflowException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
BufferOverflowException::BufferOverflowException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
BufferOverflowException::BufferOverflowException(UnicodeString* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferOverflowException::BufferOverflowException(UnicodeString* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferOverflowException::~BufferOverflowException() {
}


} /* namespace alinous */

