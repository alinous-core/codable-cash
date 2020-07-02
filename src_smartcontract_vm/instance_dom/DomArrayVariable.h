/*
 * DomArrayVariable.h
 *
 *  Created on: 2020/07/02
 *      Author: iizuka
 */

#ifndef INSTANCE_DOM_DOMARRAYVARIABLE_H_
#define INSTANCE_DOM_DOMARRAYVARIABLE_H_

#include "instance_dom/AbstractDomInstance.h"

#include "instance/IInstanceContainer.h"

namespace alinous {

class VirtualMachine;

class DomArrayVariable : public AbstractDomInstance, public IInstanceContainer {
public:
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
};

} /* namespace alinous */

#endif /* INSTANCE_DOM_DOMARRAYVARIABLE_H_ */
