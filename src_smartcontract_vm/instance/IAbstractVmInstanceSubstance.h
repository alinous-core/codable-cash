/*
 * IAbstractVmInstanceSubstance.h
 *
 *  Created on: 2020/03/21
 *      Author: iizuka
 */

#ifndef INSTANCE_IABSTRACTVMINSTANCESUBSTANCE_H_
#define INSTANCE_IABSTRACTVMINSTANCESUBSTANCE_H_

namespace alinous {

class AbstractReference;
class VirtualMachine;

class IAbstractVmInstanceSubstance {
public:
	IAbstractVmInstanceSubstance();
	virtual ~IAbstractVmInstanceSubstance();

	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) const = 0;
};

} /* namespace alinous */

#endif /* INSTANCE_IABSTRACTVMINSTANCESUBSTANCE_H_ */
