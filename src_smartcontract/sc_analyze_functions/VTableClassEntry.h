/*
 * VTableClassEntry.h
 *
 *  Created on: 2019/11/26
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_
#define SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_

#include "base/HashMap.h"
#include "base/ArrayList.h"

namespace alinous {

class AnalyzedType;
class AnalyzedClass;
class AnalyzeContext;
class UnicodeString;
class VTableMethodEntry;
class MethodNameCollection;
class ClassDeclare;
class MethodDeclare;
class MemberVariableTable;

class VTableClassEntry {
public:
	VTableClassEntry(AnalyzedClass* aclass);
	virtual ~VTableClassEntry();

	void buildVtable(AnalyzeContext* actx);
	VTableMethodEntry* findEntry(AnalyzeContext* actx, const UnicodeString* methodName, ArrayList<AnalyzedType>* types);
	MethodNameCollection* getMethodEntryCollection(const UnicodeString* methodName) const noexcept;

	MemberVariableTable* getMemberVariableTable() const noexcept;
	VTableMethodEntry* getVTableMethodEntry(const UnicodeString* callSignature) const noexcept;

private:
	void buildMethodSelf(ClassDeclare* clazz, AnalyzeContext* actx);
	void buildMethodsuper(ClassDeclare* clazz, AnalyzeContext* actx);
	void dobuildMethodSuperClass(ClassDeclare* clazz, AnalyzeContext* actx);

	void addMethodEntry(MethodDeclare* method);
	void addVirtualMethodImplEntry(MethodDeclare* method);
	void addSuperMethodEntry(MethodDeclare* method);
	void addSuperVirtualMethodImplEntry(MethodDeclare* method);

	MethodDeclare* getSuperClassMethod(MethodDeclare* method) noexcept;

	void addMethodNameEntry(VTableMethodEntry* entry) noexcept;

	void buildMemberVariables(ClassDeclare* clazz, AnalyzeContext* actx) noexcept;
	void doBuildMemberVariables(ClassDeclare* clazz, AnalyzeContext* actx) noexcept;

private:
	AnalyzedClass* aclass;
	HashMap<UnicodeString, VTableMethodEntry> methods;
	HashMap<UnicodeString, MethodNameCollection> methodsNames;

	MemberVariableTable* variables;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_ */
