/*
 * ObjectReference.h
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_OBJECTREFERENCE_H_
#define INSTANCE_REF_OBJECTREFERENCE_H_

#include "instance/instance_ref/AbstractReference.h"

namespace alinous {

class AbstractVmInstance;
class VmStringInstance;

class ObjectReference : public AbstractReference {
public:
	static constexpr uint8_t CLASS_INSTANCE {1};
	static constexpr uint8_t STRING_INSTANCE {2};

	explicit ObjectReference(IAbstractVmInstanceSubstance* owner, uint8_t type, uint8_t instanceType);
	virtual ~ObjectReference();

	static ObjectReference* createObjectReference(IAbstractVmInstanceSubstance* owner, VmClassInstance* clazzInst, VirtualMachine* vm);
	static ObjectReference* createStringReference(IAbstractVmInstanceSubstance* owner, VmStringInstance* clazzInst, VirtualMachine* vm);

	virtual bool isPrimitive() const noexcept;
	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;

	void setInstance(IAbstractVmInstanceSubstance* instance) noexcept;

	virtual void substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm);
	virtual void resetOnGc() noexcept;

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
	virtual const UnicodeString* toString() const noexcept;

	virtual bool isNull() const noexcept;
	virtual int valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;

private:
	AbstractExtObject* createNullObject(const UnicodeString* name, VTableRegistory* table);

private:
	IAbstractVmInstanceSubstance* instance;
	uint8_t instanceType;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_OBJECTREFERENCE_H_ */
