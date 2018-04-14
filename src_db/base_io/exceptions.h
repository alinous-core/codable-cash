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
	BufferUnderflowException() throw();
	BufferUnderflowException(Exception* cause) throw();
	BufferUnderflowException(UnicodeString* message) throw();
	BufferUnderflowException(UnicodeString* message, Exception* cause) throw();

	virtual ~BufferUnderflowException();

	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* BASE_IO_EXCEPTIONS_H_ */
