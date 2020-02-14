/*
 * ParseErrorHandler.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_PARSEERRORHANDLER_H_
#define SC_PARSEERRORHANDLER_H_

#include "alinous_lang/ErrorHandler.h"
#include "base/ArrayList.h"

namespace alinous {
using namespace alinouslang;

class CompileError;

class ParseErrorHandler : public ErrorHandler {
public:
	ParseErrorHandler();
	virtual ~ParseErrorHandler();

	virtual void handleUnexpectedToken(int expectedKind, const JJString& expectedToken, Token *actual, AlinousLang *parser);

	bool hasError() const noexcept;

	const ArrayList<CompileError>& getList() const {
		return list;
	}

private:
	ArrayList<CompileError> list;
};

} /* namespace alinous */

#endif /* SC_PARSEERRORHANDLER_H_ */
