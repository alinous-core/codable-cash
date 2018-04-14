/*
 * exceptions.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_IO_EXCEPTIONS_H_
#define BASE_IO_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class BufferUnderflowException : public Exception{
public:
	BufferUnderflowException() noexcept;
	BufferUnderflowException(Exception* cause) noexcept;
	BufferUnderflowException(UnicodeString* message) noexcept;
	BufferUnderflowException(UnicodeString* message, Exception* cause) noexcept;
	virtual ~BufferUnderflowException();
	static const wchar_t* defaultMessage;
};

class BufferOverflowException : public Exception{
public:
	BufferOverflowException() noexcept;
	BufferOverflowException(Exception* cause) noexcept;
	BufferOverflowException(UnicodeString* message) noexcept;
	BufferOverflowException(UnicodeString* message, Exception* cause) noexcept;
	virtual ~BufferOverflowException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* BASE_IO_EXCEPTIONS_H_ */
