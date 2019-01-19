/*
 * ClassDeclare.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSDECLARE_H_
#define SC_DECLARE_CLASSDECLARE_H_

#include "sc/CodeElement.h"

#include "base/ArrayList.h"

namespace alinous {

class ClassDeclareBlock;
class UnicodeString;
class MethodDeclare;
class MemberVariableDeclare;

class ClassDeclare : public CodeElement {
public:
	ClassDeclare();
	virtual ~ClassDeclare();

	void setBlock(ClassDeclareBlock* block) noexcept;
	void setName(UnicodeString* name) noexcept;
	void addMethod(MethodDeclare* method) noexcept;
	void addVariable(MemberVariableDeclare* variable) noexcept;
private:
	ClassDeclareBlock* block;
	UnicodeString* name;

	ArrayList<MethodDeclare> methods;
	ArrayList<MemberVariableDeclare> variables;

};

} /* namespace alinous */

#endif /* SC_DECLARE_CLASSDECLARE_H_ */
