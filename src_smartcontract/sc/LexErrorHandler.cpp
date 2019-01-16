/*
 * LexErrorHandler.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc/LexErrorHandler.h"
#include "sc/LexError.h"
#include "base/UnicodeString.h"

namespace codablecash {

LexErrorHandler::LexErrorHandler() {
}

LexErrorHandler::~LexErrorHandler() {
	this->list.deleteElements();
}

void LexErrorHandler::lexicalError(bool EOFSeen, int lexState, int errorLine,
		int errorColumn, const JJString& errorAfter, JJChar curChar,
		AlinousLangTokenManager* token_manager) {
	UnicodeString* errorAfterStr = new UnicodeString(errorAfter.c_str());
	UnicodeString* endoutedChar = new UnicodeString(L"");;
	if(EOFSeen){
		endoutedChar->append(L"EOF");
	}
	else{
		endoutedChar->append(curChar);
	}

	LexError* er = new LexError(errorAfterStr, endoutedChar, errorLine, errorColumn);
	this->list.addElement(er);
}

bool codablecash::LexErrorHandler::hasError() const noexcept {
	return !this->list.isEmpty();
}


} /* namespace codablecash */
