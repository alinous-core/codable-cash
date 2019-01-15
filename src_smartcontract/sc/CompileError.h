/*
 * CompileError.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_COMPILEERROR_H_
#define SC_COMPILEERROR_H_

namespace alinous {
class UnicodeString;
}

namespace codablecash {
using namespace alinous;

class CompileError {
public:
	CompileError(UnicodeString* expectedToken, UnicodeString* actualToken, int line, int column);
	virtual ~CompileError();

private:
	UnicodeString* expectedToken;
	UnicodeString* actualToken;
	int line;
	int column;

};

} /* namespace codablecash */

#endif /* SC_COMPILEERROR_H_ */
