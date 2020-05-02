/*
 * ClassTypeReference.h
 *
 *  Created on: 2020/04/29
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_CLASSTYPEREFERENCE_H_
#define INSTANCE_REF_CLASS_STATIC_CLASSTYPEREFERENCE_H_

#include "instance_ref/AbstractReference.h"
#include "instance/IAbstractVmInstanceSubstance.h"

namespace alinous {

class AnalyzedType;

class ClassTypeReference : public AbstractReference, public IAbstractVmInstanceSubstance {
public:
	ClassTypeReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm, const AnalyzedType* type);
	virtual ~ClassTypeReference();

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual int valueCompare(IAbstractVmInstanceSubstance* right);


	//
	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual uint8_t getInstType() const noexcept;

	virtual AnalyzedType getRuntimeType() const noexcept;

	virtual const VMemList<AbstractReference>* getInstReferences() const noexcept;
	virtual int instHashCode() const noexcept;
	virtual bool instIsPrimitive() const noexcept;
	virtual bool instIsNull() const noexcept;

	virtual int instValueCompare(IAbstractVmInstanceSubstance* right);
	virtual AbstractExtObject* instToClassExtObject(const UnicodeString* name, VTableRegistory* table);
private:
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_CLASSTYPEREFERENCE_H_ */
