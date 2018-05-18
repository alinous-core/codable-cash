/*
 * exceptions.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base_io/exceptions.h"
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
BufferUnderflowException::BufferUnderflowException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferUnderflowException::BufferUnderflowException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
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
BufferOverflowException::BufferOverflowException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferOverflowException::BufferOverflowException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BufferOverflowException::~BufferOverflowException() {
}


} /* namespace alinous */

