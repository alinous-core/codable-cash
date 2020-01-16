/*
 * AnalyzeContext.h
 *
 *  Created on: 2019/05/22
 *      Author: iizuka
 */

#ifndef SC_ANALYZECONTEXT_H_
#define SC_ANALYZECONTEXT_H_

#include "base/HashMap.h"
#include "base/ArrayList.h"
#include <initializer_list>

namespace alinous {

class VirtualMachine;
class UnicodeString;
class PackageSpace;
class ValidationError;
class CodeElement;
class AnalyzedClass;
class ClassDeclare;
class AnalyzeStackManager;
class TypeResolver;
class AnalyzedClass;
class VTableRegistory;

class AnalyzeContext {
public:
	AnalyzeContext();
	virtual ~AnalyzeContext();

	void setVm(VirtualMachine* vm) noexcept;
	PackageSpace* getPackegeSpace(const UnicodeString* spaceName) noexcept;

	void addValidationError(int errorCode, CodeElement* element, const UnicodeString* msg, std::initializer_list<const UnicodeString*> params) noexcept;
	void addValidationError(int errorCode, CodeElement* element, const wchar_t* msg, std::initializer_list<const UnicodeString*> params) noexcept;

	bool hasError() noexcept;

	AnalyzedClass* getAnalyzedClass(CodeElement* clazz);
	TypeResolver* getTypeResolver() const noexcept;
	AnalyzeStackManager* getAnalyzeStackManager() const noexcept;

	void setThisClass(AnalyzedClass* thisClass) noexcept;
	AnalyzedClass* getThisClass() const noexcept;
	void popThisClass() noexcept;

	void analyzeClassInheritance();

	VTableRegistory* getVtableRegistory() const noexcept;

	void setCurrentElement(CodeElement* current) noexcept;
	CodeElement* getCurrentElement() const noexcept;

private:
	void analyzeMembers(PackageSpace* space) noexcept;
	void analyzeMember(AnalyzedClass* cls) noexcept;

private:
	VirtualMachine* vm;
	HashMap<UnicodeString, PackageSpace> *packageSpaces;
	ArrayList<ValidationError> verrorList;
	AnalyzeStackManager* stack;
	TypeResolver* typeResolver;
	ArrayList<AnalyzedClass>* thisClasses;
	VTableRegistory* vtableReg;

	CodeElement* current;
};

} /* namespace alinous */

#endif /* SC_ANALYZECONTEXT_H_ */
