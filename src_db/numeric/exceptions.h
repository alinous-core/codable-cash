/*
 * exceptions.h
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#ifndef NUMERIC_EXCEPTIONS_H_
#define NUMERIC_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class ArithmeticException : public Exception{
public:
	ArithmeticException(const char* srcfile, int srcline) noexcept;
	ArithmeticException(Exception* cause, const char* srcfile, int srcline) noexcept;
	ArithmeticException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	ArithmeticException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~ArithmeticException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* NUMERIC_EXCEPTIONS_H_ */
