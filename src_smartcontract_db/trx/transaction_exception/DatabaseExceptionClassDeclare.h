/*
 * DatabaseExceptionClassDeclare.h
 *
 *  Created on: 2020/05/25
 *      Author: iizuka
 */

#ifndef TRANSACTION_EXCEPTION_DATABASEEXCEPTIONCLASSDECLARE_H_
#define TRANSACTION_EXCEPTION_DATABASEEXCEPTIONCLASSDECLARE_H_

#include "instance/instance_exception_class/AbstractExceptionClassDeclare.h"

namespace alinous {

class DatabaseExceptionClassDeclare : public AbstractExceptionClassDeclare {
public:
	static UnicodeString NAME;
	static AnalyzedClass* createAnalyzedClass() noexcept;
	static void throwException(const UnicodeString* msg, VirtualMachine* vm, const CodeElement* element) noexcept;

	DatabaseExceptionClassDeclare();
	virtual ~DatabaseExceptionClassDeclare();

	virtual const UnicodeString* getName() noexcept;
	virtual const UnicodeString* getFullQualifiedName() noexcept;

	virtual ClassDeclare* getBaseClass() const noexcept;

	virtual IVmInstanceFactory* getFactory() const noexcept;
};

} /* namespace alinous */

#endif /* TRANSACTION_EXCEPTION_DATABASEEXCEPTIONCLASSDECLARE_H_ */
