/*
 * VmClassInstance.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef INSTANCE_VMCLASSINSTANCE_H_
#define INSTANCE_VMCLASSINSTANCE_H_

#include "instance/AbstractVmInstance.h"
#include "instance/IInstanceContainer.h"
#include "instance/instance_parts/VMemList.h"


namespace alinous {

class AnalyzedClass;
class AbstractReference;
class VirtualMachine;
class GcManager;
class IVmInstanceFactory;

class VmClassInstance : public AbstractVmInstance, public IInstanceContainer {
public:
	VmClassInstance(AnalyzedClass* clazz, VirtualMachine* vm);
	VmClassInstance(uint8_t type, AnalyzedClass* clazz, VirtualMachine* vm);
	virtual ~VmClassInstance();

	static VmClassInstance* createObject(AnalyzedClass* clazz, VirtualMachine* vm);
	void init(VirtualMachine* vm);

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
	virtual const UnicodeString* toString() const noexcept;

	virtual const VMemList<AbstractReference>* getReferences() const noexcept;
	virtual void removeInnerRefs(GcManager* gc) noexcept;
	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* reg);

	virtual int valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;

	AnalyzedClass* getAnalyzedClass() const noexcept;

private:
	static IVmInstanceFactory* findFactory(AnalyzedClass* clazz) noexcept;

protected:
	AnalyzedClass* const clazz;
	VMemList<AbstractReference> members;
};

} /* namespace alinous */

#endif /* INSTANCE_VMCLASSINSTANCE_H_ */
