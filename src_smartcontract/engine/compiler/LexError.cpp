/*
 * LexError.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "engine/compiler/LexError.h"
#include "base/UnicodeString.h"

namespace alinous {

LexError::LexError(UnicodeString* errorAfter, UnicodeString* encoutedChar, int line, int column) {
	this->errorAfter = errorAfter;
	this->encoutedChar = encoutedChar;
	this->line = line;
	this->column = column;
}

LexError::~LexError() {
	delete this->errorAfter;
	delete this->encoutedChar;
}

} /* namespace alinous */
