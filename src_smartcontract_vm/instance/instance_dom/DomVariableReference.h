/*
 * DomVariableReference.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_DOM_DOMVARIABLEREFERENCE_H_
#define INSTANCE_DOM_DOMVARIABLEREFERENCE_H_

#include "instance/instance_ref/AbstractReference.h"

namespace alinous {

class IAbstractVmInstanceSubstance;
class VirtualMachine;
class AbstractDomInstance;

class DomVariableReference : public AbstractReference {
public:
	DomVariableReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm, AbstractDomInstance* inst);
	virtual ~DomVariableReference();

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual void substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm);
	virtual void resetOnGc() noexcept;
	virtual bool isNull() const noexcept;
	virtual bool isDom() const noexcept;

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
	virtual const UnicodeString* toString() const noexcept;

	virtual int valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;

private:
	AbstractDomInstance* inst;
};

} /* namespace alinous */

#endif /* INSTANCE_DOM_DOMVARIABLEREFERENCE_H_ */
