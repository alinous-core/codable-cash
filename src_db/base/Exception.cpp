/*
 * Exception.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include <base/Exception.h>

#include "base/UnicodeString.h"

namespace alinous {

Exception::Exception() throw() : cause(nullptr), message(nullptr) {
}

Exception::Exception(Exception* cause) throw() : cause(cause), message(nullptr) {
}
Exception::Exception(UnicodeString* message) throw(): cause(nullptr), message(nullptr) {
}
Exception::Exception(UnicodeString* message, Exception* cause) throw() : cause(cause), message(nullptr){

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
