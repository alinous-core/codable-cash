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
	//AnalyzedClass(const AnalyzedClass& inst);
	explicit AnalyzedClass(ClassDeclare* clazz);
	virtual ~AnalyzedClass();

	void addMemberVariableDeclare(MemberVariableDeclare* member);
	ArrayList<MemberVariableDeclare>* getMemberVariableDeclareList() noexcept;
	void addMemberMethodDeclare(MethodDeclare* method);

	void setExtends(AnalyzedClass* clazz) noexcept;
	void addImplements(AnalyzedClass* clazz) noexcept;

	MethodDeclare* getDefaultConstructor() noexcept;
	const UnicodeString* toString() noexcept;
private:
	ClassDeclare* clazz;

	AnalyzedClass* extends;
	ArrayList<AnalyzedClass> implements;

	HashMap<UnicodeString, MemberVariableDeclare>* variables;
	ArrayList<MemberVariableDeclare> variablesList;

	ArrayList<MethodDeclare> constructors;
	HashMap<UnicodeString, MethodDeclare>* methods;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZEDCLASS_H_ */
