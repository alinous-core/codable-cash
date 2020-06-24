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
	VmStringInstance(const VmStringInstance& inst) = delete;
	VmStringInstance(VirtualMachine* vm, const UnicodeString* str);
	virtual ~VmStringInstance();

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual int valueCompare(IAbstractVmInstanceSubstance* right);
	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual uint8_t getInstType() const noexcept;
	virtual AnalyzedType getRuntimeType() const noexcept;
	virtual int hashCode() const noexcept;

	virtual const VMemList<AbstractReference>* getInstReferences() const noexcept;
	virtual int instHashCode() const noexcept;
	virtual bool instIsPrimitive() const noexcept;
	virtual bool instIsNull() const noexcept;
	virtual int instValueCompare(IAbstractVmInstanceSubstance* right);
	virtual AbstractExtObject* instToClassExtObject(const UnicodeString* name, VTableRegistory* table);


	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
	virtual const UnicodeString* toString() noexcept;

	VmStringInstance* copy(VirtualMachine* vm) const;

	class ValueCompare {
	public:
		int operator() (const VmStringInstance* const _this, const  VmStringInstance* const object) const noexcept;
	};
private:
	VmString* value;
	static const VmString::ValueCompare compareFunctor;

	UnicodeString* str;
};

} /* namespace alinous */

#endif /* INSTANCE_VMSTRINGINSTANCE_H_ */
