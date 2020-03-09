/*
 * ArrayReference.h
 *
 *  Created on: 2020/02/15
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_ARRAYREFERENCE_H_
#define INSTANCE_REF_ARRAYREFERENCE_H_

#include "instance_ref/AbstractReference.h"



namespace alinous {

class VirtualMachine;
class VmArrayInstance;
template <typename T, typename C> class ArrayList;

class ArrayReference : public AbstractReference {
public:
	ArrayReference(VirtualMachine* vm);
	virtual ~ArrayReference();

	virtual AbstractVmInstance* getInstance() noexcept;
	virtual void substitute(AbstractVmInstance* rightValue, VirtualMachine* vm);
	virtual bool isNull() const noexcept;
	virtual int valueCompare(AbstractVmInstance* right);

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);


private:
	VmArrayInstance* instArray;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_ARRAYREFERENCE_H_ */
