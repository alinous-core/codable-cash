/*
 * AnalyzeContext.cpp
 *
 *  Created on: 2019/05/22
 *      Author: iizuka
 */
#include "sc_analyze/AnalyzeContext.h"
#include "base/Iterator.h"
#include "base/UnicodeString.h"

#include "sc_analyze/PackageSpace.h"
#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeStackManager.h"

#include "sc_declare/ClassDeclare.h"

#include "sc/CompilationUnit.h"
#include "sc/exceptions.h"

namespace alinous {

AnalyzeContext::AnalyzeContext() {
	this->vm = nullptr;
	this->packageSpaces = new HashMap<UnicodeString, PackageSpace>();
	this->stack = new AnalyzeStackManager();
}

AnalyzeContext::~AnalyzeContext() {
	this->vm = nullptr; // safe

	Iterator<UnicodeString>* it = this->packageSpaces->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* n = it->next();
		PackageSpace* space = this->packageSpaces->get(n);
		delete space;
	}
	delete it;

	delete this->packageSpaces;

	this->verrorList.deleteElements();
	delete this->stack;
}

void AnalyzeContext::setVm(VirtualMachine* vm) noexcept {
	this->vm = vm;
}

PackageSpace* AnalyzeContext::getPackegeSpace(const UnicodeString* spaceName) noexcept {
	PackageSpace* space = this->packageSpaces->get(spaceName);
	if(space == nullptr){
		space = new PackageSpace(spaceName);
		this->packageSpaces->put(spaceName, space);
	}

	return space;
}

void AnalyzeContext::addValidationError(const UnicodeString* msg, CodeElement* element) noexcept {
	ValidationError* error = new ValidationError(ValidationError::ERROR, element, msg);
	this->verrorList.addElement(error);
}

void AnalyzeContext::addValidationError(const wchar_t* msg, CodeElement* element) noexcept {
	UnicodeString str(msg);
	addValidationError(&str, element);
}

bool alinous::AnalyzeContext::hasError() noexcept {
	return !this->verrorList.isEmpty();
}

AnalyzedClass* AnalyzeContext::getAnalyzedClass(CodeElement* element) {
	ClassDeclare* dec = element->getClassDeclare();
	if(dec == nullptr){
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}

	CompilationUnit* unit = dec->getCompilationUnit();
	PackageSpace* pkg = getPackegeSpace(unit->getPackageName());

	return pkg->getClass(dec->getName());
}

} /* namespace alinous */
