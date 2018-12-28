/*
 * exceptions.cpp
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#include "btree/exceptions.h"
#include "base/UnicodeString.h"
#include <btree/exceptions.h>

namespace alinous {

const wchar_t* NodeStructureException::defaultMessage =
		L"Node structure is wrong ";

NodeStructureException::NodeStructureException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
NodeStructureException::NodeStructureException(Exception* cause,
		const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
}
NodeStructureException::NodeStructureException(const wchar_t* message,
		const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
NodeStructureException::NodeStructureException(const wchar_t* message,
		Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {
	this->message = new UnicodeString(defaultMessage);
	this->message->append(message);
}
NodeStructureException::~NodeStructureException() {
}

} /* namespace alinous */


