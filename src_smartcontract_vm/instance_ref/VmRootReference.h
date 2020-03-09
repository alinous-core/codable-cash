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
class VmClassInstance;

class VmRootReference : public AbstractReference {
public:
	explicit VmRootReference(VirtualMachine* vm);
	virtual ~VmRootReference();

	void setMainInstance(VmClassInstance* mainInst) noexcept;
	virtual AbstractVmInstance* getInstance() noexcept;

	void clearInnerReferences();

	PrimitiveReference* newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm);

	virtual int valueCompare(const AbstractVmInstance* right);
private:
	VirtualMachine* vm;
	VmClassInstance* mainInst;
	StaticInstanceHolder* staticHolder;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_VMROOTREFERENCE_H_ */
