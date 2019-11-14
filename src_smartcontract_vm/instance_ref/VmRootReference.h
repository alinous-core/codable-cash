/*
 * VmRootReference.h
 *
 *  Created on: 2019/07/08
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_VMROOTREFERENCE_H_
#define INSTANCE_REF_VMROOTREFERENCE_H_

#include "instance_ref/AbstractReference.h"


namespace alinous {

class VirtualMachine;
class StaticInstanceHolder;

class VmRootReference : public AbstractReference {
public:
	VmRootReference(VirtualMachine* vm);
	virtual ~VmRootReference();

	void setMainInstance(AbstractVmInstance* mainInst) noexcept;


private:
	VirtualMachine* vm;
	AbstractVmInstance* mainInst;
	StaticInstanceHolder* staticHolder;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_VMROOTREFERENCE_H_ */
