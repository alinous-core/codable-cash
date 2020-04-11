/*
 * AbstructProgramException.h
 *
 *  Created on: 2020/03/06
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_ABSTRACTPROGRAMEXCEPTION_H_
#define INSTANCE_EXCEPTION_ABSTRACTPROGRAMEXCEPTION_H_

#include "base/Exception.h"

namespace alinous {

class AbstractProgramException : public Exception {
public:
	AbstractProgramException(const char* srcfile, int srcline) noexcept;
	AbstractProgramException(Exception* cause, const char* srcfile, int srcline) noexcept;
	AbstractProgramException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	AbstractProgramException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~AbstractProgramException();
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_ABSTRACTPROGRAMEXCEPTION_H_ */
