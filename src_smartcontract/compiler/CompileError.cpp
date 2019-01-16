/*
 * CompileError.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "compiler/CompileError.h"
#include "base/UnicodeString.h"

namespace alinous {

CompileError::CompileError(UnicodeString* expectedToken, UnicodeString* actualToken, int line, int column) {
	this->expectedToken = expectedToken;
	this->actualToken = actualToken;
	this->line = line;
	this->column = column;
}

CompileError::~CompileError() {
	if(this->expectedToken){
		delete this->expectedToken;
	}
	if(this->actualToken){
		delete this->actualToken;
	}

}

} /* namespace alinous */
