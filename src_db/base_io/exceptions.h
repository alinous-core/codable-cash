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
	BufferUnderflowException(const char* srcfile, int srcline) noexcept;
	BufferUnderflowException(Exception* cause, const char* srcfile, int srcline) noexcept;
	BufferUnderflowException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	BufferUnderflowException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~BufferUnderflowException();
	static const wchar_t* defaultMessage;
};

class BufferOverflowException : public Exception{
public:
	BufferOverflowException(const char* srcfile, int srcline) noexcept;
	BufferOverflowException(Exception* cause, const char* srcfile, int srcline) noexcept;
	BufferOverflowException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	BufferOverflowException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~BufferOverflowException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* BASE_IO_EXCEPTIONS_H_ */
