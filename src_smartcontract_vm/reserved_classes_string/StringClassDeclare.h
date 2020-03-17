/*
 * StringClassDeclare.h
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#ifndef RESERVED_CLASSES_STRING_STRINGCLASSDECLARE_H_
#define RESERVED_CLASSES_STRING_STRINGCLASSDECLARE_H_

#include "sc_declare/ClassDeclare.h"

namespace alinous {

class StringClassDeclare : public ClassDeclare {
public:
	StringClassDeclare();
	virtual ~StringClassDeclare();

	void init(VirtualMachine* vm);

	const UnicodeString* getName() noexcept;
	const UnicodeString* getFullQualifiedName() noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	ClassDeclare* getBaseClass() const noexcept;

	ArrayList<MethodDeclare>* getMethods() noexcept;
	ArrayList<MemberVariableDeclare>* getMemberVariables() noexcept;
};

} /* namespace alinous */

#endif /* RESERVED_CLASSES_STRING_STRINGCLASSDECLARE_H_ */
