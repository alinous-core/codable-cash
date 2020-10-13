/*
 * VmTransactionHandlerException.cpp
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#include "vm/vm_trx/VmTransactionHandlerException.h"

#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* VmTransactionHandlerException::defaultMessage = L"Transacton handler exception.";

VmTransactionHandlerException::VmTransactionHandlerException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
VmTransactionHandlerException::VmTransactionHandlerException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
VmTransactionHandlerException::VmTransactionHandlerException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
VmTransactionHandlerException::VmTransactionHandlerException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
VmTransactionHandlerException::~VmTransactionHandlerException() {
}
} /* namespace alinous */
