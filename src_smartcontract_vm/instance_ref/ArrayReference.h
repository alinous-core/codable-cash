/*
 * ArrayReference.h
 *
 *  Created on: 2020/02/15
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_ARRAYREFERENCE_H_
#define INSTANCE_REF_ARRAYREFERENCE_H_

#include "instance_ref/AbstractReference.h"
#include "instance_parts/VMemList.h"
#include "instance/IInstanceContainer.h"


namespace alinous {

class VirtualMachine;

class ArrayReference : public AbstractReference, public IInstanceContainer {
public:
	ArrayReference(VirtualMachine* vm);
	virtual ~ArrayReference();

	virtual void removeInnerRefs(GcManager* gc) noexcept;

	void add(AbstractVmInstance* inst);

private:
	VMemList<AbstractVmInstance>* array;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_ARRAYREFERENCE_H_ */
