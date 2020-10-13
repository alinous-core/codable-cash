/*
 * StringClassDeclare.h
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#ifndef RESERVED_CLASSES_STRING_STRINGCLASSDECLARE_H_
#define RESERVED_CLASSES_STRING_STRINGCLASSDECLARE_H_

#include "instance/reserved_classes/AbstractReservedClassDeclare.h"

namespace alinous {

class UnicodeString;
class AnalyzedClass;

class StringClassDeclare : public AbstractReservedClassDeclare {
public:
	static UnicodeString NAME;

	static AnalyzedClass* createAnalyzedClass() noexcept;

	StringClassDeclare();
	virtual ~StringClassDeclare();

	virtual const UnicodeString* getName() noexcept;
	virtual const UnicodeString* getFullQualifiedName() noexcept;

	virtual ClassDeclare* getBaseClass() const noexcept;
};

} /* namespace alinous */

#endif /* RESERVED_CLASSES_STRING_STRINGCLASSDECLARE_H_ */
