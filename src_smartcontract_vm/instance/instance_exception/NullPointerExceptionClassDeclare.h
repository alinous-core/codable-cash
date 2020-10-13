/*
 * NullPointerExceptionClassDeclare.h
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_NULLPOINTEREXCEPTIONCLASSDECLARE_H_
#define INSTANCE_EXCEPTION_NULLPOINTEREXCEPTIONCLASSDECLARE_H_

#include "instance/instance_exception_class/AbstractExceptionClassDeclare.h"

namespace alinous {

class NullPointerExceptionClassDeclare : public AbstractExceptionClassDeclare {
public:
	static UnicodeString NAME;
	static AnalyzedClass* createAnalyzedClass() noexcept;
	static void throwException(VirtualMachine* vm, const CodeElement* element) noexcept;

	NullPointerExceptionClassDeclare();
	virtual ~NullPointerExceptionClassDeclare();

	virtual const UnicodeString* getName() noexcept;
	virtual const UnicodeString* getFullQualifiedName() noexcept;

	virtual ClassDeclare* getBaseClass() const noexcept;

	virtual IVmInstanceFactory* getFactory() const noexcept;
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_NULLPOINTEREXCEPTIONCLASSDECLARE_H_ */
