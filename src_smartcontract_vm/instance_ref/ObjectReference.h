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
class VmStringInstance;

class ObjectReference : public AbstractReference {
public:
	explicit ObjectReference(IAbstractVmInstanceSubstance* owner, uint8_t type);
	virtual ~ObjectReference();

	static ObjectReference* createObjectReference(IAbstractVmInstanceSubstance* owner, VmClassInstance* clazzInst, VirtualMachine* vm);
	static ObjectReference* createObjectReference(IAbstractVmInstanceSubstance* owner, VmClassInstance* clazzInst, VirtualMachine* vm, bool doGc);
	static ObjectReference* createStringReference(IAbstractVmInstanceSubstance* owner, VmStringInstance* clazzInst, VirtualMachine* vm);

	virtual bool isPrimitive() const noexcept;
	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;

	void setInstance(IAbstractVmInstanceSubstance* instance) noexcept;

	virtual void substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm);

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
	virtual bool isNull() const noexcept;
	virtual int valueCompare(IAbstractVmInstanceSubstance* right);
private:
	IAbstractVmInstanceSubstance* instance;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_OBJECTREFERENCE_H_ */
