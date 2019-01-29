/*
 * exceptions.cpp
 *
 *  Created on: 2018/11/11
 *      Author: iizuka
 */

#include "exceptions.h"
#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* BlockFileStorageException::defaultMessage = L"FileStorage error. ";

BlockFileStorageException::BlockFileStorageException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
BlockFileStorageException::BlockFileStorageException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
BlockFileStorageException::BlockFileStorageException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BlockFileStorageException::BlockFileStorageException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BlockFileStorageException::~BlockFileStorageException() {
}

const wchar_t* BinaryFormatException::defaultMessage = L"FileStorage error. ";

BinaryFormatException::BinaryFormatException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
BinaryFormatException::BinaryFormatException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
BinaryFormatException::BinaryFormatException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BinaryFormatException::BinaryFormatException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
BinaryFormatException::~BinaryFormatException() {
}
} /* namespace alinous */
