/*
 * DomRuntimeReference.h
 *
 *  Created on: 2020/06/27
 *      Author: iizuka
 */

#ifndef INSTANCE_DOM_DOMRUNTIMEREFERENCE_H_
#define INSTANCE_DOM_DOMRUNTIMEREFERENCE_H_

#include "instance/instance_ref/AbstractReference.h"

namespace alinous {

class IAbstractVmInstanceSubstance;
class VirtualMachine;

class DomRuntimeReference : public AbstractReference {
public:
	DomRuntimeReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual ~DomRuntimeReference();

	virtual bool isPrimitive() const noexcept;

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual void substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm);
	virtual void resetOnGc() noexcept;
	virtual bool isNull() const noexcept;

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
	virtual const UnicodeString* toString() const noexcept;

	virtual int valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;

	//AbstractReference* getInnerReference() const noexcept {
	//	return this->reference;
	//}
private:
	AbstractReference* reference;
};

} /* namespace alinous */

#endif /* INSTANCE_DOM_DOMRUNTIMEREFERENCE_H_ */
