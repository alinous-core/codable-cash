/*
 * ParseErrorHandler.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "engine/compiler/ParseErrorHandler.h"
#include "engine/compiler/CompileError.h"
#include "base/UnicodeString.h"

namespace alinous {

ParseErrorHandler::ParseErrorHandler() {
}

ParseErrorHandler::~ParseErrorHandler() {
	this->list.deleteElements();
}

void ParseErrorHandler::handleUnexpectedToken(int expectedKind,	const JJString& expectedToken, Token* actual, AlinousLang* parser) {
	CompileError* error = new CompileError(new UnicodeString(expectedToken.c_str()),
			new UnicodeString(actual->image.c_str()), actual->beginLine, actual->beginColumn);
	list.addElement(error);

	//ErrorHandler::handleUnexpectedToken(expectedKind, expectedToken, actual, parser);
}

bool ParseErrorHandler::hasError() const noexcept {
	return !this->list.isEmpty();
}

} /* namespace alinous */
