/*
 * AbstractDomInstance.h
 *
 *  Created on: 2020/07/01
 *      Author: iizuka
 */

#ifndef INSTANCE_DOM_ABSTRACTDOMINSTANCE_H_
#define INSTANCE_DOM_ABSTRACTDOMINSTANCE_H_

#include "instance/AbstractVmInstance.h"
#include "instance/IInstanceContainer.h"

namespace alinous {

class VirtualMachine;

class AbstractDomInstance : public AbstractVmInstance, public IInstanceContainer {
public:
	AbstractDomInstance(VirtualMachine* vm, uint8_t type);
	virtual ~AbstractDomInstance();
};

} /* namespace alinous */

#endif /* INSTANCE_DOM_ABSTRACTDOMINSTANCE_H_ */
