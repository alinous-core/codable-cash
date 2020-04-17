/*
 * ZeroDivisionExceptionClassDeclare.h
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_ZERODIVISIONEXCEPTIONCLASSDECLARE_H_
#define INSTANCE_EXCEPTION_ZERODIVISIONEXCEPTIONCLASSDECLARE_H_

#include "reserved_classes/AbstractReservedClassDeclare.h"

namespace alinous {

class ZeroDivisionExceptionClassDeclare : public AbstractReservedClassDeclare {
public:
	static UnicodeString NAME;

	ZeroDivisionExceptionClassDeclare();
	virtual ~ZeroDivisionExceptionClassDeclare();
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_ZERODIVISIONEXCEPTIONCLASSDECLARE_H_ */
