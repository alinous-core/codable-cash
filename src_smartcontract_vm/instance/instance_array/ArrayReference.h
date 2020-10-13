/*
 * ArrayReference.h
 *
 *  Created on: 2020/02/15
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_ARRAYREFERENCE_H_
#define INSTANCE_REF_ARRAYREFERENCE_H_

#include "instance/instance_ref/AbstractReference.h"



namespace alinous {

class VirtualMachine;
class VmArrayInstance;
template <typename T, typename C> class ArrayList;
class IAbstractVmInstanceSubstance;

class ArrayReference : public AbstractReference {
public:
	ArrayReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	ArrayReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm, VmArrayInstance* instArray);
	virtual ~ArrayReference();

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual void substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm);
	virtual void resetOnGc() noexcept;
	virtual bool isNull() const noexcept;
	virtual int valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
	virtual const UnicodeString* toString() const noexcept;

private:
	VmArrayInstance* instArray;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_ARRAYREFERENCE_H_ */
