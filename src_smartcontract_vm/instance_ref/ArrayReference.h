/*
 * ArrayReference.h
 *
 *  Created on: 2020/02/15
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_ARRAYREFERENCE_H_
#define INSTANCE_REF_ARRAYREFERENCE_H_

#include "instance_ref/AbstractReference.h"



namespace alinous {

class VirtualMachine;

class ArrayReference : public AbstractReference {
public:
	ArrayReference(VirtualMachine* vm);
	virtual ~ArrayReference();

private:
};

} /* namespace alinous */

#endif /* INSTANCE_REF_ARRAYREFERENCE_H_ */
