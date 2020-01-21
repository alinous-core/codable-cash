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

#include "sc_analyze_functions/FunctionScoreCalc.h"
#include "sc_analyze_functions/VTableMethodEntry.h"
#include "sc_analyze_functions/MethodNameCollection.h"
#include "sc_analyze_functions/MethodScore.h"

#include "sc_analyze_variables/MemberVariableTable.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/MethodDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"
#include "sc_declare/MemberVariableDeclare.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"


namespace alinous {

VTableClassEntry::VTableClassEntry(AnalyzedClass* aclass) {
	this->aclass = aclass;
	this->variables = new MemberVariableTable();
}

VTableClassEntry::~VTableClassEntry() {
	{
		Iterator<UnicodeString>* it = this->methods.keySet()->iterator(); __STP(it);
		while(it->hasNext()){
			const UnicodeString* key = it->next();
			VTableMethodEntry* m = this->methods.get(key);
			delete m;
		}
	}

	{
		Iterator<UnicodeString>* it = this->methodsNames.keySet()->iterator(); __STP(it);
		while(it->hasNext()){
			const UnicodeString* key = it->next();
			MethodNameCollection* col = this->methodsNames.get(key);
			delete col;
		}
	}

	this->aclass = nullptr;
	delete this->variables;
}

void VTableClassEntry::buildVtable(AnalyzeContext* actx) {
	ClassDeclare* clazz = this->aclass->getClassDeclare();

	buildMethodSelf(clazz, actx);

	// super class's methods
	buildMethodsuper(clazz, actx);

	// member variables
	buildMemberVariables(clazz, actx);
}

void VTableClassEntry::buildMemberVariables(ClassDeclare* clazz, AnalyzeContext* actx) noexcept {
	ArrayList<ClassDeclare> list;

	ClassDeclare* cls = clazz;
	while(cls != nullptr){
		list.addElement(cls);
		cls = cls->getBaseClass();
	}

	int maxLoop = list.size();
	for(int i = 0; i != maxLoop; ++i){
		ClassDeclare* cls = list.get(i);
		doBuildMemberVariables(cls, actx);
	}
}

void VTableClassEntry::doBuildMemberVariables(ClassDeclare* clazz, AnalyzeContext* actx) noexcept {
	ArrayList<MemberVariableDeclare>* list = clazz->getMemberVariables();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* mem = list->get(i);
		const UnicodeString* name = mem->getName();

		if(this->variables->hasEntry(name)){
			// error
			actx->addValidationError(ValidationError::CODE_CLASS_MEMBER_ALREADY_EXISTS, clazz, L"The member '{0}' is defined in super class.", {mem->getName()});
			continue;
		}

		this->variables->addEntry(name, mem);
	}
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
	addMethodNameEntry(entry);
}

void VTableClassEntry::addSuperVirtualMethodImplEntry(MethodDeclare* method) {
	VTableMethodEntry* entry = new VTableMethodEntry(method, VTableMethodEntry::METHOD_VIRTUAL_SUPER);
	this->methods.put(method->getCallSignature(), entry);
	addMethodNameEntry(entry);
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
	addMethodNameEntry(entry);
}

void VTableClassEntry::addVirtualMethodImplEntry(MethodDeclare* method) {
	VTableMethodEntry* entry = new VTableMethodEntry(method, VTableMethodEntry::METHOD_VIRTUAL);
	this->methods.put(method->getCallSignature(), entry);
	addMethodNameEntry(entry);
}

/**
 * needs actx->setCurrentElement(this);
 */
VTableMethodEntry* VTableClassEntry::findEntry(AnalyzeContext* actx, const UnicodeString* methodName, ArrayList<AnalyzedType>* types) {
	FunctionScoreCalc calc(this);

	MethodScore* score = calc.findMethod(methodName, types);
	if(score == nullptr){
		int errorCode = calc.getErrorCode();
		if(errorCode == FunctionScoreCalc::ERROR_AMBIGOUS){
			ArrayList<MethodScore>* amList = calc.getAmbigousList();
			actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_AMBIGOUS, actx->getCurrentElement(), L"The method '{0}()' has ambiguous arguments.", {methodName});
		}
		return nullptr;
	}

	return score->getEntry();
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

void VTableClassEntry::addMethodNameEntry(VTableMethodEntry* entry) noexcept {
	const UnicodeString* methodName = entry->getName();

	MethodNameCollection* collection = this->methodsNames.get(methodName);
	if(collection == nullptr){
		collection = new MethodNameCollection();
		this->methodsNames.put(methodName, collection);
	}

	collection->addMethodEntry(entry);
}

MethodNameCollection* VTableClassEntry::getMethodEntryCollection(const UnicodeString* methodName) const noexcept {
	return this->methodsNames.get(methodName);
}

MemberVariableTable* VTableClassEntry::getMemberVariableTable() const noexcept {
	return this->variables;
}

VTableMethodEntry* VTableClassEntry::getVTableMethodEntry(const UnicodeString* callSignature) const noexcept {
	return this->methods.get(callSignature);
}


} /* namespace alinous */
