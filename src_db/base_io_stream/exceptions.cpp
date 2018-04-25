/*
 * exceptions.cpp
 *
 *  Created on: 2018/04/25
 *      Author: iizuka
 */

#include "base_io_stream/exceptions.h"
#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* FileOpenException::defaultMessage = L"Failed in Opening File ";

FileOpenException::FileOpenException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
FileOpenException::FileOpenException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
FileOpenException::FileOpenException(UnicodeString* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
FileOpenException::FileOpenException(UnicodeString* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
FileOpenException::~FileOpenException() {
}


} /* namespace alinous */
