/*
 * exceptions.cpp
 *
 *  Created on: 2019/01/14
 *      Author: iizuka
 */

#include "bc/exceptions.h"
#include "base/UnicodeString.h"

namespace codablecash {

const wchar_t* MulformattedTransactionBinaryException::defaultMessage = L"Format of Transaction binary is wrong. ";

MulformattedTransactionBinaryException::MulformattedTransactionBinaryException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
MulformattedTransactionBinaryException::MulformattedTransactionBinaryException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
MulformattedTransactionBinaryException::MulformattedTransactionBinaryException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
MulformattedTransactionBinaryException::MulformattedTransactionBinaryException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
MulformattedTransactionBinaryException::~MulformattedTransactionBinaryException() {
}

} /* namespace codablecash */
