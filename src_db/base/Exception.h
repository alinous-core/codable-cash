/*
 * Exception.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_EXCEPTION_H_
#define BASE_EXCEPTION_H_

namespace alinous {

class UnicodeString;

class Exception {
public:
	Exception(const char* srcfile, int srcline) noexcept;
	Exception(Exception* cause, const char* srcfile, int srcline) noexcept;
	Exception(UnicodeString* message, const char* srcfile, int srcline) noexcept;
	Exception(UnicodeString* message, Exception* cause, const char* srcfile, int srcline) noexcept;

	virtual ~Exception();

protected:
	UnicodeString* message;
	Exception* cause;
	const char* srcfile;
	int srcline;
};

} /* namespace alinous */

#endif /* BASE_EXCEPTION_H_ */
