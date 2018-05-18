/*
 * exceptions.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/exceptions.h"
#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* FileStorageException::defaultMessage = L"FileStorage error. ";

FileStorageException::FileStorageException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
FileStorageException::FileStorageException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
FileStorageException::FileStorageException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
FileStorageException::FileStorageException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
FileStorageException::~FileStorageException() {
}


} /* namespace alinous */
