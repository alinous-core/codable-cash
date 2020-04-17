/*
 * ArrayOutOfBoundsExceptionClassDeclare.h
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTIONCLASSDECLARE_H_
#define INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTIONCLASSDECLARE_H_

#include "reserved_classes/AbstractReservedClassDeclare.h"

namespace alinous {

class ArrayOutOfBoundsExceptionClassDeclare : public AbstractReservedClassDeclare {
public:
	static UnicodeString NAME;
	static AnalyzedClass* createAnalyzedClass() noexcept;

	ArrayOutOfBoundsExceptionClassDeclare();
	virtual ~ArrayOutOfBoundsExceptionClassDeclare();

	virtual const UnicodeString* getName() noexcept;
	virtual const UnicodeString* getFullQualifiedName() noexcept;

	virtual ClassDeclare* getBaseClass() const noexcept;

	virtual IVmInstanceFactory* getFactory() const noexcept;
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_ARRAYOUTOFBOUNDSEXCEPTIONCLASSDECLARE_H_ */
