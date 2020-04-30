/*
 * ClassTypeReference.h
 *
 *  Created on: 2020/04/29
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_CLASSTYPEREFERENCE_H_
#define INSTANCE_REF_CLASS_STATIC_CLASSTYPEREFERENCE_H_

#include "instance_ref/AbstractReference.h"

namespace alinous {

class AnalyzedType;

class ClassTypeReference : public AbstractReference {
public:
	ClassTypeReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm, const AnalyzedType* type);
	virtual ~ClassTypeReference();

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual int valueCompare(IAbstractVmInstanceSubstance* right);
private:
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_CLASSTYPEREFERENCE_H_ */
