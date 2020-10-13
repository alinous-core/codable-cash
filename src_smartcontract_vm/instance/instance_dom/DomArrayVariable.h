/*
 * DomArrayVariable.h
 *
 *  Created on: 2020/07/02
 *      Author: iizuka
 */

#ifndef INSTANCE_DOM_DOMARRAYVARIABLE_H_
#define INSTANCE_DOM_DOMARRAYVARIABLE_H_

#include "instance/instance_dom/AbstractDomInstance.h"

#include "instance/IInstanceContainer.h"

#include "instance/instance_parts/VMemList.h"

namespace alinous {

class VirtualMachine;
class UnicodeString;
class DomRuntimeReference;

class DomArrayVariable : public AbstractDomInstance {
public:
	static const UnicodeString LENGTH;

	explicit DomArrayVariable(VirtualMachine* vm);
	virtual ~DomArrayVariable();

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

	void add(VirtualMachine* vm, IAbstractVmInstanceSubstance* inst);
	int size() const noexcept;
	DomRuntimeReference* get(int i) const noexcept;
private:
	VMemList<DomRuntimeReference>* array;
	mutable UnicodeString* str;
	mutable VMemList<AbstractReference> list;
};

} /* namespace alinous */

#endif /* INSTANCE_DOM_DOMARRAYVARIABLE_H_ */
