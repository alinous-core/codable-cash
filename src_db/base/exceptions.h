/*
 * exceptions.h
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#ifndef BASE_EXCEPTIONS_H_
#define BASE_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class NumberFormatException : public Exception{
public:
	NumberFormatException() noexcept;
	NumberFormatException(Exception* cause) noexcept;
	NumberFormatException(UnicodeString* message) noexcept;
	NumberFormatException(UnicodeString* message, Exception* cause) noexcept;
	virtual ~NumberFormatException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* BASE_EXCEPTIONS_H_ */
