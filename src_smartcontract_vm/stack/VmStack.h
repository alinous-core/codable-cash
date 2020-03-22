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
	explicit VmStack(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual ~VmStack();

	void addInnerReference(AbstractReference* ref);
	AbstractReference* get(int pos) const noexcept;

	virtual const VMemList<AbstractReference>* getReferences() const noexcept;
	virtual void removeInnerRefs(GcManager* gc) noexcept;


	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual uint8_t getInstType() const noexcept;
	virtual const VMemList<AbstractReference>* getInstReferences() const noexcept;
	virtual int instHashCode() const noexcept;
	virtual bool instIsNull() const noexcept;
	virtual int instValueCompare(IAbstractVmInstanceSubstance* right);
	virtual AbstractExtObject* instToClassExtObject(const UnicodeString* name, VTableRegistory* table);

	virtual int valueCompare(IAbstractVmInstanceSubstance* right);

private:
	VMemList<AbstractReference>* stack;
	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* STACK_VMSTACK_H_ */
