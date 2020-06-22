/*
 * DomVariableInstance.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_DOM_DOMVARIABLEINSTANCE_H_
#define INSTANCE_DOM_DOMVARIABLEINSTANCE_H_

#include "instance/AbstractVmInstance.h"
#include "instance/IInstanceContainer.h"

namespace alinous {

class AbstractReference;
class DomVariableReference;

class DomVariableInstance : public AbstractVmInstance, public IInstanceContainer {
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
	virtual int instValueCompare(IAbstractVmInstanceSubstance* right);
	virtual AbstractExtObject* instToClassExtObject(const UnicodeString* name, VTableRegistory* table);

	virtual const UnicodeString* toString() noexcept;


	virtual int valueCompare(IAbstractVmInstanceSubstance* right);

private:
	AbstractReference* valueRef;
	VMemList<AbstractReference>* properties;
};

} /* namespace alinous */

#endif /* INSTANCE_DOM_DOMVARIABLEINSTANCE_H_ */
