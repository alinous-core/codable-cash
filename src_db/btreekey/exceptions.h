/*
 * exceptions.h
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#ifndef BTREEKEY_EXCEPTIONS_H_
#define BTREEKEY_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class KeyFormatException : public Exception{
public:
	KeyFormatException(const char* srcfile, int srcline) noexcept;
	KeyFormatException(Exception* cause, const char* srcfile, int srcline) noexcept;
	KeyFormatException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	KeyFormatException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~KeyFormatException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* BTREEKEY_EXCEPTIONS_H_ */
