/*
 * exceptions.h
 *
 *  Created on: 2018/04/25
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_EXCEPTIONS_H_
#define BASE_IO_STREAM_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class FileOpenException : public Exception{
public:
	FileOpenException(const char* srcfile, int srcline) noexcept;
	FileOpenException(Exception* cause, const char* srcfile, int srcline) noexcept;
	FileOpenException(UnicodeString* message, const char* srcfile, int srcline) noexcept;
	FileOpenException(UnicodeString* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~FileOpenException();
	static const wchar_t* defaultMessage;
};

class FileIOException : public Exception{
public:
	FileIOException(const char* srcfile, int srcline) noexcept;
	FileIOException(Exception* cause, const char* srcfile, int srcline) noexcept;
	FileIOException(UnicodeString* message, const char* srcfile, int srcline) noexcept;
	FileIOException(UnicodeString* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~FileIOException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_EXCEPTIONS_H_ */
