/*
 * LexError.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_LEXERROR_H_
#define SC_LEXERROR_H_

namespace alinous {
class UnicodeString;
}

namespace codablecash {
using namespace alinous;

class LexError {
public:
	LexError(UnicodeString* errorAfter, UnicodeString* endoutedChar, int line, int column);
	virtual ~LexError();

private:
	UnicodeString* errorAfter;
	UnicodeString* encoutedChar;
	int line;
	int column;
};

} /* namespace codablecash */

#endif /* SC_LEXERROR_H_ */
