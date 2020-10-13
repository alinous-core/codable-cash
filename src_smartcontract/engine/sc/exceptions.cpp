/*
 * exceptions.cpp
 *
 *  Created on: 2019/03/19
 *      Author: iizuka
 */

#include "engine/sc/exceptions.h"
#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* MulformattedScBinaryException::defaultMessage = L"Format of Smart Contract binary is wrong. ";

MulformattedScBinaryException::MulformattedScBinaryException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
MulformattedScBinaryException::MulformattedScBinaryException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
MulformattedScBinaryException::MulformattedScBinaryException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
MulformattedScBinaryException::MulformattedScBinaryException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
MulformattedScBinaryException::~MulformattedScBinaryException() {
}

} /* namespace alinous */
