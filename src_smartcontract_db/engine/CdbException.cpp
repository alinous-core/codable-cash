/*
 * DatabaseException.cpp
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#include "engine/CdbException.h"

#include "base/UnicodeString.h"

#include "transaction_log/AbstractTransactionLog.h"

namespace codablecash {

const wchar_t* CdbException::defaultMessage = L"Buffer is under flown";

CdbException::CdbException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->cmd = nullptr;
}
CdbException::CdbException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->cmd = nullptr;
}
CdbException::CdbException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
	this->cmd = nullptr;
}
CdbException::CdbException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
	this->cmd = nullptr;
}
CdbException::~CdbException() {
	delete this->cmd;
}


} /* namespace codablecash */
