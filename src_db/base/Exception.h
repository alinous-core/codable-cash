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
	Exception() throw();
	Exception(Exception* cause) throw();
	Exception(UnicodeString* message) throw();
	Exception(UnicodeString* message, Exception* cause) throw();

	virtual ~Exception();

protected:
	UnicodeString* message;
	Exception* cause;
};

} /* namespace alinous */

#endif /* BASE_EXCEPTION_H_ */
