/*
 * VmRootReference.h
 *
 *  Created on: 2019/07/08
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_VMROOTREFERENCE_H_
#define INSTANCE_REF_VMROOTREFERENCE_H_

#include "instance/instance_ref/AbstractReference.h"
#include <cstdint>

#include "instance/IAbstractVmInstanceSubstance.h"

namespace alinous {

class VirtualMachine;
class StaticInstanceHolder;
class StaticClassReferenceHolder;
class PrimitiveReference;
class VmClassInstance;
class VmStringInstance;
class VmRootReference;

class VmRootReference : public AbstractReference, public IAbstractVmInstanceSubstance {
public:
	explicit VmRootReference(VirtualMachine* vm);
	virtual ~VmRootReference();

	void setMainInstance(VmClassInstance* mainInst) noexcept;
	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual uint8_t getInstType() const noexcept;
	virtual AnalyzedType getRuntimeType() const noexcept;

	virtual const VMemList<AbstractReference>* getInstReferences() const noexcept;
	virtual int instHashCode() const noexcept;
	virtual bool instIsPrimitive() const noexcept;
	virtual bool instIsNull() const noexcept;
	virtual int instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;
	virtual AbstractExtObject* instToClassExtObject(const UnicodeString* name, VTableRegistory* table);

	void clearInnerReferences();
	void releaseMainInstance(GcManager* gc);

	virtual void resetOnGc() noexcept;


	PrimitiveReference* newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm);
	VmStringInstance* newStringConstReferenece(VmRootReference* rootRef, const UnicodeString* str, VirtualMachine* vm);

	StaticClassReferenceHolder* getStaticClassReferenceHolder() const noexcept;

	virtual int valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;
private:
	VirtualMachine* vm;
	AbstractReference* mainInst;
	StaticInstanceHolder* staticHolder;
	StaticClassReferenceHolder* classStaticHolder;

};

} /* namespace alinous */

#endif /* INSTANCE_REF_VMROOTREFERENCE_H_ */
