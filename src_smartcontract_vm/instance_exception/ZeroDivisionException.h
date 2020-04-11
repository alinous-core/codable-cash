/*
 * ZeroDivisionException.h
 *
 *  Created on: 2020/03/06
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARITHMETIC_ZERODIVISIONEXCEPTION_H_
#define SC_EXPRESSION_ARITHMETIC_ZERODIVISIONEXCEPTION_H_

#include "instance_exception/AbstractProgramException.h"

namespace alinous {

class ZeroDivisionException : public AbstractProgramException {
public:
	ZeroDivisionException(const char* srcfile, int srcline) noexcept;
	ZeroDivisionException(Exception* cause, const char* srcfile, int srcline) noexcept;
	ZeroDivisionException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	ZeroDivisionException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~ZeroDivisionException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARITHMETIC_ZERODIVISIONEXCEPTION_H_ */
