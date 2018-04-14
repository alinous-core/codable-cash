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
	Exception() noexcept;
	Exception(Exception* cause) noexcept;
	Exception(UnicodeString* message) noexcept;
	Exception(UnicodeString* message, Exception* cause) noexcept;

	virtual ~Exception();

protected:
	UnicodeString* message;
	Exception* cause;
};

} /* namespace alinous */

#endif /* BASE_EXCEPTION_H_ */
