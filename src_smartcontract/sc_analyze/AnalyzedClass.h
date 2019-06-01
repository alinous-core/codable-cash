/*
 * AnalyzedClass.h
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZEDCLASS_H_
#define SC_ANALYZE_ANALYZEDCLASS_H_

#include "base/HashMap.h"
#include "base/ArrayList.h"

namespace alinous {

class ClassDeclare;
class UnicodeString;
class MemberVariableDeclare;
class MethodDeclare;

class AnalyzedClass {
public:
	explicit AnalyzedClass(ClassDeclare* clazz);
	virtual ~AnalyzedClass();

	void addMemberVariableDeclare(MemberVariableDeclare* member);
	void addMemberMethodDeclare(MethodDeclare* method);

	MethodDeclare* getDefaultConstructor() noexcept;
private:
	ClassDeclare* clazz;

	HashMap<UnicodeString, MemberVariableDeclare>* variables;

	ArrayList<MethodDeclare>* constructors;
	HashMap<UnicodeString, MethodDeclare>* methods;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZEDCLASS_H_ */
