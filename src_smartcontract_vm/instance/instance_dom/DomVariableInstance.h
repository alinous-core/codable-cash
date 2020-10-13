/*
 * DomVariableInstance.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_DOM_DOMVARIABLEINSTANCE_H_
#define INSTANCE_DOM_DOMVARIABLEINSTANCE_H_

#include "instance_dom/AbstractDomInstance.h"

#include "instance_parts/VMemHashmap.h"

#include "instance_string/VmStringInstance.h"


namespace alinous {

class AbstractReference;
class DomVariableReference;
class DomRuntimeReference;

class DomVariableInstance : public AbstractDomInstance {
public:
	explicit DomVariableInstance(VirtualMachine* vm);
	virtual ~DomVariableInstance();

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

	void putProperty(VirtualMachine* vm, const VmStringInstance* key, IAbstractVmInstanceSubstance* substance) noexcept;
	DomRuntimeReference* getProperty(VirtualMachine* vm, const VmStringInstance* key) noexcept;
private:
	VMemHashmap<VmStringInstance, DomRuntimeReference>* properties;

	mutable VMemList<AbstractReference>* list;
	mutable UnicodeString* str;
};

} /* namespace alinous */

#endif /* INSTANCE_DOM_DOMVARIABLEINSTANCE_H_ */
