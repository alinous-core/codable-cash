/*
 * VmStringInstance.h
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#ifndef INSTANCE_VMSTRINGINSTANCE_H_
#define INSTANCE_VMSTRINGINSTANCE_H_

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/AbstractVmInstance.h"

#include "instance_string/VmString.h"


namespace alinous {

class VirtualMachine;

class VmStringInstance : public AbstractVmInstance, public IAbstractVmInstanceSubstance {
public:
	VmStringInstance(VirtualMachine* vm, const UnicodeString* str);
	virtual ~VmStringInstance();

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual int valueCompare(IAbstractVmInstanceSubstance* right);
	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual uint8_t getInstType() const noexcept;
	virtual const VMemList<AbstractReference>* getInstReferences() const noexcept;
	virtual int instHashCode() const noexcept;

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
private:
	VmString* value;
	static const VmString::ValueCompare compareFunctor;
};

} /* namespace alinous */

#endif /* INSTANCE_VMSTRINGINSTANCE_H_ */
