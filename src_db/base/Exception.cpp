/*
 * Exception.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include <base/Exception.h>

#include "base/UnicodeString.h"

namespace alinous {

Exception::Exception() noexcept : cause(nullptr), message(nullptr) {
}

Exception::Exception(Exception* cause) noexcept : cause(cause), message(nullptr) {
}
Exception::Exception(UnicodeString* message) noexcept: cause(nullptr), message(nullptr) {
}
Exception::Exception(UnicodeString* message, Exception* cause) noexcept : cause(cause), message(nullptr){

}

Exception::~Exception() {
	if(this->message != nullptr){
		delete this->message;
	}
	if(this->cause != nullptr){
		delete this->cause;
	}
}

} /* namespace alinous */
