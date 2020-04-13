/*
 * ExceptionClassDeclare.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_CLASS_EXCEPTIONCLASSDECLARE_H_
#define INSTANCE_EXCEPTION_CLASS_EXCEPTIONCLASSDECLARE_H_

#include "reserved_classes/AbstractReservedClassDeclare.h"

namespace alinous {

class AnalyzedClass;

class ExceptionClassDeclare : public AbstractReservedClassDeclare {
public:
	static UnicodeString NAME;
	static AnalyzedClass* createAnalyzedClass() noexcept;

	ExceptionClassDeclare();
	virtual ~ExceptionClassDeclare();

	virtual const UnicodeString* getName() noexcept;
	virtual const UnicodeString* getFullQualifiedName() noexcept;

	virtual ClassDeclare* getBaseClass() const noexcept;
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_CLASS_EXCEPTIONCLASSDECLARE_H_ */
