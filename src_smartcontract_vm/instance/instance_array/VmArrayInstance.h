/*
 * VmArrayInstance.h
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#ifndef INSTANCE_VMARRAYINSTANCE_H_
#define INSTANCE_VMARRAYINSTANCE_H_
#include <cstdint>

#include "instance/IInstanceContainer.h"
#include "instance/instance_parts/VMemList.h"

#include "instance/AbstractVmInstance.h"


namespace alinous {
class VirtualMachine;

class VmArrayInstance : public AbstractVmInstance, public IInstanceContainer {
public:
	VmArrayInstance(VirtualMachine* vm, int length, const AnalyzedType& atype);
	virtual ~VmArrayInstance();

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual uint8_t getInstType() const noexcept;
	virtual AnalyzedType getRuntimeType() const noexcept;

	virtual void removeInnerRefs(GcManager* gc) noexcept;
	virtual const VMemList<AbstractReference>* getReferences() const noexcept;
	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* reg);
	virtual const VMemList<AbstractReference>* getInstReferences() const noexcept;
	virtual int instHashCode() const noexcept;
	virtual bool instIsPrimitive() const noexcept;
	virtual bool instIsNull() const noexcept;
	virtual int instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;
	virtual AbstractExtObject* instToClassExtObject(const UnicodeString* name, VTableRegistory* table);

	virtual const UnicodeString* toString() const noexcept;


	virtual int valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;

	void setReference(VirtualMachine* vm, int pos, AbstractReference* ref) noexcept;
	AbstractReference* getReference(VirtualMachine* vm, int pos);
	int size() const noexcept;
private:
	VMemList<AbstractReference>* array;
	int length;

	AnalyzedType* atype;

	mutable UnicodeString* str;
};

} /* namespace alinous */

#endif /* INSTANCE_VMARRAYINSTANCE_H_ */
