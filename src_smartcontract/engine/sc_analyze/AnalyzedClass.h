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
class ClassDeclare;
class MethodDeclare;
class AbstractReference;
template <typename T, typename C> class ArrayList;
class AnalyzeContext;
class AnalyzedType;
class IVmInstanceFactory;

class AnalyzedClass {
public:
	AnalyzedClass(const AnalyzedClass& inst);
	explicit AnalyzedClass(ClassDeclare* clazz);
	virtual ~AnalyzedClass();

	void addMemberVariableDeclare(MemberVariableDeclare* member);
	ArrayList<MemberVariableDeclare>* getMemberVariableDeclareList() noexcept;
	void addStaticMemberVariableDeclare(MemberVariableDeclare* member) noexcept;

	void addMemberMethodDeclare(MethodDeclare* method);

	void setExtends(AnalyzedClass* clazz) noexcept;
	AnalyzedClass* getExtends() const noexcept;
	void addImplements(AnalyzedClass* clazz) noexcept;
	const ArrayList<AnalyzedClass>* getImplements() const noexcept;

	MethodDeclare* getDefaultConstructor() noexcept;
	MethodDeclare* findMethod(const UnicodeString* name, ArrayList<AnalyzedType>* argumentTypeList) noexcept;

	void buildVtable(AnalyzeContext* actx) noexcept;

	ClassDeclare* getClassDeclare() const noexcept;
	int getInheritIndex() const noexcept;
	void setInheritIndex(int inheritIndex) noexcept;


	const UnicodeString* toString() noexcept;
	const UnicodeString* getSignatureName() noexcept;
	const UnicodeString* getFullQualifiedName() noexcept;

	bool equals(AnalyzedClass* other) noexcept;

	bool hasBaseClass(AnalyzedClass* clazz) noexcept;

	void setFactory(IVmInstanceFactory* factory) noexcept;
	IVmInstanceFactory* getFactory() const noexcept;

	void setReserved(bool reserved) noexcept;
	bool isReserved() const noexcept;

	bool isInterface() const noexcept;
private:
	//void bulidMethodVTable(AnalyzeContext* actx, MethodDeclare* method) noexcept;
	//AnalyzedClass* findBaseClassOfMethod(AnalyzedClass* currentClass, MethodDeclare* method) noexcept;


private:
	ClassDeclare* clazz;

	AnalyzedClass* extends;
	ArrayList<AnalyzedClass> implements;

	HashMap<UnicodeString, MemberVariableDeclare>* variables;
	ArrayList<MemberVariableDeclare> variablesList;

	HashMap<UnicodeString, MemberVariableDeclare>* staticVariables;

	ArrayList<MethodDeclare> constructors;
	HashMap<UnicodeString, MethodDeclare>* methods;

	IVmInstanceFactory* factory;

	UnicodeString* sig;
	bool reserved;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZEDCLASS_H_ */
