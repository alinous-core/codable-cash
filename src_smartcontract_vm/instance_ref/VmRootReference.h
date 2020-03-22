/*
 * VmRootReference.h
 *
 *  Created on: 2019/07/08
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_VMROOTREFERENCE_H_
#define INSTANCE_REF_VMROOTREFERENCE_H_

#include "instance_ref/AbstractReference.h"
#include <cstdint>

#include "instance/IAbstractVmInstanceSubstance.h"

namespace alinous {

class VirtualMachine;
class StaticInstanceHolder;
class PrimitiveReference;
class VmClassInstance;
class VmStringInstance;

class VmRootReference : public AbstractReference, public IAbstractVmInstanceSubstance {
public:
	explicit VmRootReference(VirtualMachine* vm);
	virtual ~VmRootReference();

	void setMainInstance(VmClassInstance* mainInst) noexcept;
	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) const;

	void clearInnerReferences();

	PrimitiveReference* newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm);
	VmStringInstance* newStringConstReferenece(const UnicodeString* str, VirtualMachine* vm);

	virtual int valueCompare(AbstractVmInstance* right);
private:
	VirtualMachine* vm;
	VmClassInstance* mainInst;
	StaticInstanceHolder* staticHolder;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_VMROOTREFERENCE_H_ */
