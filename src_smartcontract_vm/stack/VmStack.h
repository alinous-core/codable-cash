/*
 * VmStack.h
 *
 *  Created on: 2019/06/30
 *      Author: iizuka
 */

#ifndef STACK_VMSTACK_H_
#define STACK_VMSTACK_H_

#include "instance/AbstractVmInstance.h"

namespace alinous {

class VmStack : public AbstractVmInstance {
public:
	VmStack();
	virtual ~VmStack();
};

} /* namespace alinous */

#endif /* STACK_VMSTACK_H_ */
