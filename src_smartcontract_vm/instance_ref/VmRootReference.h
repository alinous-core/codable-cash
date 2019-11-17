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


namespace alinous {

class VirtualMachine;
class StaticInstanceHolder;
class PrimitiveReference;

class VmRootReference : public AbstractReference {
public:
	explicit VmRootReference(VirtualMachine* vm);
	virtual ~VmRootReference();

	void setMainInstance(AbstractVmInstance* mainInst) noexcept;

	PrimitiveReference* newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm);
private:
	VirtualMachine* vm;
	AbstractVmInstance* mainInst;
	StaticInstanceHolder* staticHolder;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_VMROOTREFERENCE_H_ */
