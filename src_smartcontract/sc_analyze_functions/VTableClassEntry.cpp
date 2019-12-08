/*
 * VTableClassEntry.cpp
 *
 *  Created on: 2019/11/26
 *      Author: iizuka
 */

#include "sc_analyze_functions/VTableClassEntry.h"

#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_analyze_functions/VTableMethodEntry.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/MethodDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

namespace alinous {

VTableClassEntry::VTableClassEntry(AnalyzedClass* aclass) {
	this->aclass = aclass;
}

VTableClassEntry::~VTableClassEntry() {
	Iterator<UnicodeString>* it = this->methods.keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		VTableMethodEntry* m = this->methods.get(key);
		delete m;
	}

	this->aclass = nullptr;
}

void VTableClassEntry::buildVtable(AnalyzeContext* actx) {
	ClassDeclare* clazz = this->aclass->getClassDeclare();

	buildMethodSelf(clazz, actx);

	// super class's methods
	buildMethodsuper(clazz, actx);
}


void VTableClassEntry::buildMethodsuper(ClassDeclare* clazz, AnalyzeContext* actx) {
	ClassDeclare* cls = clazz->getBaseClass();
	while(cls != nullptr){
		dobuildMethodSuperClass(cls, actx);

		cls = cls->getBaseClass();
	}
}

void VTableClassEntry::dobuildMethodSuperClass(ClassDeclare* clazz,	AnalyzeContext* actx) {
	ArrayList<MethodDeclare>* list = clazz->getMethods();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = list->get(i);
		const UnicodeString* sigStr = method->getCallSignature();
		AnalyzedType* retType = method->getReturnedType();

		VTableMethodEntry* entry = this->methods.get(sigStr);
		if(entry != nullptr){
			continue;
		}

		MethodDeclare* superMethod = getSuperClassMethod(method);
		if(superMethod == nullptr){
			addSuperMethodEntry(method);
			continue;
		}

		AnalyzedType* retTypeSuper = superMethod->getReturnedType();
		if(!retType->equals(retTypeSuper)){
			actx->addValidationError(ValidationError::CODE_VIRTUAL_FUNC_WITH_DIFFERENT_RETURN, method, L"The method '{0}()' has supuer class method with different return type.", {method->getName()});
			continue;
		}

		addSuperVirtualMethodImplEntry(method);
	}
}

void VTableClassEntry::addSuperMethodEntry(MethodDeclare* method) {
	VTableMethodEntry* entry = new VTableMethodEntry(method, VTableMethodEntry::METHOD_NORMAL);
	this->methods.put(method->getCallSignature(), entry);
}

void VTableClassEntry::addSuperVirtualMethodImplEntry(MethodDeclare* method) {
	VTableMethodEntry* entry = new VTableMethodEntry(method, VTableMethodEntry::METHOD_VIRTUAL_SUPER);
	this->methods.put(method->getCallSignature(), entry);
}


void VTableClassEntry::buildMethodSelf(ClassDeclare* clazz,	AnalyzeContext* actx) {
	ArrayList<MethodDeclare>* list = clazz->getMethods();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = list->get(i);
		const UnicodeString* sigStr = method->getCallSignature();
		AnalyzedType* retType = method->getReturnedType();

		MethodDeclare* superMethod = getSuperClassMethod(method);
		if(superMethod == nullptr){
			addMethodEntry(method);
			continue;
		}

		AnalyzedType* retTypeSuper = superMethod->getReturnedType();
		if(!retType->equals(retTypeSuper)){
			actx->addValidationError(ValidationError::CODE_VIRTUAL_FUNC_WITH_DIFFERENT_RETURN, method, L"The method '{0}()' has supuer class method with different return type.", {method->getName()});
			continue;
		}

		addVirtualMethodImplEntry(method);
	}
}


void VTableClassEntry::addMethodEntry(MethodDeclare* method) {
	VTableMethodEntry* entry = new VTableMethodEntry(method, VTableMethodEntry::METHOD_NORMAL);
	this->methods.put(method->getCallSignature(), entry);
}

void VTableClassEntry::addVirtualMethodImplEntry(MethodDeclare* method) {
	VTableMethodEntry* entry = new VTableMethodEntry(method, VTableMethodEntry::METHOD_VIRTUAL);
	this->methods.put(method->getCallSignature(), entry);
}

MethodDeclare* VTableClassEntry::getSuperClassMethod(MethodDeclare* method) noexcept {
	MethodDeclare* superMethod = nullptr;

	const UnicodeString* name = method->getName();
	ArgumentsListDeclare* argList = method->getArguments();
	ArrayList<AnalyzedType>* typeList = argList->getArgumentsAnalyzedType();

	AnalyzedClass* superClass = this->aclass->getExtends();
	while(superClass != nullptr){
		superMethod = superClass->findMethod(name, typeList);

		if(superMethod != nullptr){
			return superMethod;
		}

		superClass = superClass->getExtends();
	}

	return nullptr;
}

} /* namespace alinous */
