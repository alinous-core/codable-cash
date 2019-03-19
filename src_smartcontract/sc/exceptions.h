/*
 * exceptions.h
 *
 *  Created on: 2019/03/19
 *      Author: iizuka
 */

#ifndef SC_EXCEPTIONS_H_
#define SC_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class MulformattedScBinaryException : public Exception{
public:
	MulformattedScBinaryException(const char* srcfile, int srcline) noexcept;
	MulformattedScBinaryException(Exception* cause, const char* srcfile, int srcline) noexcept;
	MulformattedScBinaryException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	MulformattedScBinaryException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~MulformattedScBinaryException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */

#endif /* SC_EXCEPTIONS_H_ */
