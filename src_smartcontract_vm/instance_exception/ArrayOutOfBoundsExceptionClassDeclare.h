/*
 * ArrayOutOfBoundsExceptionClassDeclare.h
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTIONCLASSDECLARE_H_
#define INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTIONCLASSDECLARE_H_

#include "reserved_classes/AbstractReservedClassDeclare.h"

namespace alinous {

class ArrayOutOfBoundsExceptionClassDeclare : public AbstractReservedClassDeclare {
public:
	static UnicodeString NAME;

	ArrayOutOfBoundsExceptionClassDeclare();
	virtual ~ArrayOutOfBoundsExceptionClassDeclare();
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTIONCLASSDECLARE_H_ */
