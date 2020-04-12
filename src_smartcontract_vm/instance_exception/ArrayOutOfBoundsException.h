/*
 * ArrayOutOfBoundsException.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTION_H_
#define INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTION_H_

#include "instance_exception/AbstractProgramException.h"

namespace alinous {

class ArrayOutOfBoundsException: public AbstractProgramException {
public:
	ArrayOutOfBoundsException();
	virtual ~ArrayOutOfBoundsException();
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTION_H_ */
