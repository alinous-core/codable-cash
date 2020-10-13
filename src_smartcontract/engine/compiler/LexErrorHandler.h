/*
 * LexErrorHandler.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_LEXERRORHANDLER_H_
#define SC_LEXERRORHANDLER_H_

#include "alinous_lang/ErrorHandler.h"
#include "base/ArrayList.h"

namespace alinous {
using namespace alinouslang;

class LexError;

class LexErrorHandler : public TokenManagerErrorHandler {
public:
	LexErrorHandler();
	virtual ~LexErrorHandler();

	virtual void lexicalError(bool EOFSeen, int lexState, int errorLine, int errorColumn, const JJString& errorAfter, JJChar curChar, AlinousLangTokenManager* token_manager);

	bool hasError() const noexcept;
private:
	ArrayList<LexError> list;
};

} /* namespace alinous */

#endif /* SC_LEXERRORHANDLER_H_ */
