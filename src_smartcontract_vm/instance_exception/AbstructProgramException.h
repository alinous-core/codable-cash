/*
 * AbstructProgramException.h
 *
 *  Created on: 2020/03/06
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_ABSTRUCTPROGRAMEXCEPTION_H_
#define INSTANCE_EXCEPTION_ABSTRUCTPROGRAMEXCEPTION_H_

#include "base/Exception.h"

namespace alinous {

class AbstructProgramException : public Exception {
public:
	AbstructProgramException(const char* srcfile, int srcline) noexcept;
	AbstructProgramException(Exception* cause, const char* srcfile, int srcline) noexcept;
	AbstructProgramException(const wchar_t* message, const char* srcfile, int srcline) noexcept;
	AbstructProgramException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept;
	virtual ~AbstructProgramException();
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_ABSTRUCTPROGRAMEXCEPTION_H_ */
