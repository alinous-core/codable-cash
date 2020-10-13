/*
 * CompileError.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "engine/compiler/CompileError.h"
#include "base/UnicodeString.h"

namespace alinous {


CompileError::CompileError(const CompileError& obj) {
	this->expectedToken = new UnicodeString(obj.expectedToken);
	this->actualToken = new UnicodeString(obj.actualToken);
	this->line = obj.line;
	this->column = obj.column;
}

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
