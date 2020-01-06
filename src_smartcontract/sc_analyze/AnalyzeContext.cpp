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
#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzedClass.h"

#include "sc_analyze_functions/VTableRegistory.h"
#include "sc_analyze_functions/VTableClassEntry.h"

#include "sc_analyze_variables/MemberVariableTable.h"
#include "sc_analyze_variables/MemberVariableEntry.h"

#include "sc_declare/ClassDeclare.h"

#include "sc/CompilationUnit.h"
#include "sc/exceptions.h"

#include "base/StackRelease.h"

namespace alinous {

AnalyzeContext::AnalyzeContext() {
	this->vm = nullptr;
	this->packageSpaces = new HashMap<UnicodeString, PackageSpace>();
	this->stack = new AnalyzeStackManager();
	this->typeResolver = new TypeResolver(this);
	this->thisClass = nullptr;
	this->vtableReg = new VTableRegistory();
	this->current = nullptr;
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
	delete this->typeResolver;
	delete this->vtableReg;
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

void AnalyzeContext::addValidationError(int errorCode, CodeElement* element, const UnicodeString* msg, std::initializer_list<const UnicodeString*> params) noexcept {
	ValidationError* error = new ValidationError(ValidationError::ERROR, errorCode, element, msg, params);
	this->verrorList.addElement(error);
}

void AnalyzeContext::addValidationError(int errorCode, CodeElement* element, const wchar_t* msg, std::initializer_list<const UnicodeString*> params) noexcept {
	UnicodeString str(msg);
	addValidationError(errorCode, element, &str, params);
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

TypeResolver* AnalyzeContext::getTypeResolver() const noexcept {
	return this->typeResolver;
}

AnalyzeStackManager* AnalyzeContext::getAnalyzeStackManager() const noexcept {
	return this->stack;
}

void AnalyzeContext::setThisClass(AnalyzedClass* thisClass) noexcept {
	this->thisClass = thisClass;
}

AnalyzedClass* AnalyzeContext::getThisClass() const noexcept {
	return this->thisClass;
}

void AnalyzeContext::analyzeClassInheritance() {
	Iterator<UnicodeString>* it = this->packageSpaces->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* packageName = it->next();
		PackageSpace* space = this->packageSpaces->get(packageName);

		space->analyzeClassInheritance(this);
	}
	delete it;

	// V tables
	it = this->packageSpaces->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* packageName = it->next();
		PackageSpace* space = this->packageSpaces->get(packageName);

		space->buildVTables(this);
	}
	delete it;

	// members
	it = this->packageSpaces->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* packageName = it->next();
		PackageSpace* space = this->packageSpaces->get(packageName);

		analyzeMembers(space);
	}
	delete it;
}

void AnalyzeContext::analyzeMembers(PackageSpace* space) noexcept {
	HashMap<UnicodeString, AnalyzedClass>* map = space->getMap();

	Iterator<UnicodeString>* it = map->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* className = it->next();
		AnalyzedClass* cls = map->get(className);

		analyzeMember(cls);
	}
}

void AnalyzeContext::analyzeMember(AnalyzedClass* cls) noexcept {
	const UnicodeString* fqn = cls->getFullQualifiedName();
	VTableClassEntry* classEntry = this->vtableReg->getClassEntry(fqn, cls);

	MemberVariableTable* variables = classEntry->getMemberVariableTable();
	ArrayList<MemberVariableEntry>* list = variables->getVariableList();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableEntry* entry = list->get(i);
		MemberVariableDeclare* dec = entry->getMemberVariableDeclare();

		cls->addMemberVariableDeclare(dec);
	}
	// FIXME
}


VTableRegistory* AnalyzeContext::getVtableRegistory() const noexcept {
	return this->vtableReg;
}


void AnalyzeContext::setCurrentElement(CodeElement* current) noexcept {
	this->current = current;
}

CodeElement* AnalyzeContext::getCurrentElement() const noexcept {
	return this->current;
}

} /* namespace alinous */
