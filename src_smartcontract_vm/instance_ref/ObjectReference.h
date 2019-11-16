/*
 * ObjectReference.h
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_OBJECTREFERENCE_H_
#define INSTANCE_REF_OBJECTREFERENCE_H_

#include "instance_ref/AbstractReference.h"

namespace alinous {

class AbstractVmInstance;

class ObjectReference : public AbstractReference {
public:
	explicit ObjectReference(uint8_t type);
	virtual ~ObjectReference();

	static ObjectReference* createObjectReference(VmClassInstance* clazzInst, VirtualMachine* vm);

	virtual bool isPrimitive() const noexcept;
	virtual AbstractVmInstance* getInstance() const noexcept;

	void setInstance(AbstractVmInstance* instance) noexcept;

	virtual void substitute(AbstractVmInstance* rightValue, VirtualMachine* vm);
private:
	AbstractVmInstance* instance;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_OBJECTREFERENCE_H_ */
