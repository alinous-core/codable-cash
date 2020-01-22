/*
 * VmStack.h
 *
 *  Created on: 2019/06/30
 *      Author: iizuka
 */

#ifndef STACK_VMSTACK_H_
#define STACK_VMSTACK_H_

#include "instance_ref/AbstractReference.h"
#include "instance/IInstanceContainer.h"

#include "instance_parts/VMemList.h"

namespace alinous {

class AbstractReference;
class VirtualMachine;
class VmRootReference;

class VmStack : public AbstractReference, public IInstanceContainer {
public:
	VmStack(VirtualMachine* vm);
	virtual ~VmStack();

	void addInnerReference(AbstractReference* ref);
	AbstractReference* get(int pos) const noexcept;

	virtual const VMemList<AbstractReference>* getReferences() const noexcept;
	virtual void removeInnerRefs(GcManager* gc) noexcept;

private:
	VMemList<AbstractReference>* stack;
	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* STACK_VMSTACK_H_ */
