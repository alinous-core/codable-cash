/*
 * exceptions.cpp
 *
 *  Created on: 2019/04/14
 *      Author: iizuka
 */

#include "vm/exceptions.h"
#include "base/UnicodeString.h"

namespace alinous {

const wchar_t* VmMemoryAllocationException::defaultMessage = L"FileStorage error. ";

VmMemoryAllocationException::VmMemoryAllocationException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
VmMemoryAllocationException::VmMemoryAllocationException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
VmMemoryAllocationException::VmMemoryAllocationException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
VmMemoryAllocationException::VmMemoryAllocationException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
VmMemoryAllocationException::~VmMemoryAllocationException() {
}

} /* namespace alinous */
