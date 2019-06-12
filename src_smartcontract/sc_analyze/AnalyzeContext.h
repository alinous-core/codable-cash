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

namespace alinous {

class VirtualMachine;
class UnicodeString;
class PackageSpace;
class ValidationError;
class CodeElement;
class AnalyzedClass;
class ClassDeclare;
class AnalyzeStackManager;

class AnalyzeContext {
public:
	AnalyzeContext();
	virtual ~AnalyzeContext();

	void setVm(VirtualMachine* vm) noexcept;
	PackageSpace* getPackegeSpace(const UnicodeString* spaceName) noexcept;
	void addValidationError(const UnicodeString* msg, CodeElement* element) noexcept;
	void addValidationError(const wchar_t* msg, CodeElement* element) noexcept;

	bool hasError() noexcept;

	AnalyzedClass* getAnalyzedClass(CodeElement* clazz);

private:
	VirtualMachine* vm;
	HashMap<UnicodeString, PackageSpace> *packageSpaces;
	ArrayList<ValidationError> verrorList;
	AnalyzeStackManager* stack;
};

} /* namespace alinous */

#endif /* SC_ANALYZECONTEXT_H_ */
