/*
 * AnalyzedClass.cpp
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#include "sc_analyze/AnalyzedClass.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/MethodDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"
#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ArgumentDeclare.h"

#include "base/UnicodeString.h"
#include "base/ArrayList.h"

#include "instance_ref/AbstractReference.h"

#include "sc_analyze_functions/VTableRegistory.h"
#include "sc_analyze_functions/FunctionScoreCalc.h"
#include "sc_analyze_functions/VTableClassEntry.h"

#include "sc_analyze/IVmInstanceFactory.h"
namespace alinous {

AnalyzedClass::AnalyzedClass(const AnalyzedClass& inst) {
	this->clazz = inst.clazz;
	this->variables = new HashMap<UnicodeString, MemberVariableDeclare>();
	this->methods = new HashMap<UnicodeString, MethodDeclare>();
	this->sig = nullptr;

	Iterator<UnicodeString>* it = inst.variables->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* name = it->next();
		MemberVariableDeclare* dec = inst.variables->get(name);
		this->variables->put(name, dec);
	}
	delete it;

	int maxLoop = inst.variablesList.size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* dec = inst.variablesList.get(i);
		this->variablesList.addElement(dec);
	}

	maxLoop = inst.constructors.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* constructor = inst.constructors.get(i);
		this->constructors.addElement(constructor);
	}

	it = inst.methods->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* name = it->next();
		MethodDeclare* dec = inst.methods->get(name);
		this->methods->put(name, dec);
	}
	delete it;

	this->extends = inst.extends;
	maxLoop = inst.implements.size();
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedClass* cls = inst.implements.get(i);
		this->implements.addElement(cls);
	}

	this->factory = nullptr;
}

AnalyzedClass::AnalyzedClass(ClassDeclare* clazz) {
	this->clazz = clazz;
	this->variables = new HashMap<UnicodeString, MemberVariableDeclare>();
	this->methods = new HashMap<UnicodeString, MethodDeclare>();
	this->extends = nullptr;
	this->sig = nullptr;
	this->factory = nullptr;
}

AnalyzedClass::~AnalyzedClass() {
	this->clazz = nullptr;
	delete this->variables;
	delete this->methods;
	delete this->sig;
	delete this->factory;
}

void AnalyzedClass::addMemberVariableDeclare(MemberVariableDeclare* member) {
	this->variables->put(member->getName(), member);
	this->variablesList.addElement(member);
}

void AnalyzedClass::addMemberMethodDeclare(MethodDeclare* method) {
	if(method->isConstructor()){
		this->constructors.addElement(method);
		return;
	}

	this->methods->put(method->getName(), method);
}

ArrayList<MemberVariableDeclare>* AnalyzedClass::getMemberVariableDeclareList() noexcept {
	return &this->variablesList;
}

void AnalyzedClass::setExtends(AnalyzedClass* clazz) noexcept {
	this->extends = clazz;
}

AnalyzedClass* AnalyzedClass::getExtends() const noexcept {
	return this->extends;
}

void AnalyzedClass::addImplements(AnalyzedClass* clazz) noexcept {
	this->implements.addElement(clazz);
}

MethodDeclare* AnalyzedClass::getDefaultConstructor() noexcept {
	int maxLoop = this->constructors.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* m = this->constructors.get(i);
		ArgumentsListDeclare* args = m->getArguments();
		int num = args->getSize();
		if(num == 0){
			return m;
		}
	}

	return nullptr;
}

MethodDeclare* AnalyzedClass::findMethod(const UnicodeString* name, ArrayList<AnalyzedType>* argumentTypeList) noexcept {
	MethodDeclare* method = this->methods->get(name);
	if(method == nullptr){
		return method;
	}

	ArrayList<AnalyzedType>* argumentTypeList2 = method->getArguments()->getArgumentsAnalyzedType();

	int maxLoop = argumentTypeList->size();
	if(maxLoop != argumentTypeList2->size()){
		return nullptr;
	}

	for(int i = 0; i != maxLoop; ++i){
		AnalyzedType* atype = argumentTypeList->get(i);
		AnalyzedType* atype2 = argumentTypeList2->get(i);

		if(!atype->equals(atype2)){
			return nullptr;
		}
	}

	return method;
}


int AnalyzedClass::getInheritIndex() const noexcept {
	return this->clazz->getInheritIndex();
}

void AnalyzedClass::setInheritIndex(int inheritIndex) noexcept {
	this->clazz->setInheritIndex(inheritIndex);
}

const UnicodeString* AnalyzedClass::toString() noexcept {
	return this->clazz->getName();
}

const UnicodeString* AnalyzedClass::getSignatureName() noexcept {
	if(this->sig == nullptr){
		this->sig = new UnicodeString(L"L");

		this->sig->append(this->clazz->getFullQualifiedName());
		this->sig->append(L";");
	}
	return this->sig;
}

const UnicodeString* AnalyzedClass::getFullQualifiedName() noexcept {
	return this->clazz->getFullQualifiedName();
}


void AnalyzedClass::buildVtable(AnalyzeContext* actx) noexcept {
	VTableRegistory* vreg = actx->getVtableRegistory();
	const UnicodeString* fqn = this->clazz->getFullQualifiedName();

	VTableClassEntry* classEntry = vreg->getClassEntry(fqn, this);
	classEntry->buildVtable(actx);
}

ClassDeclare* AnalyzedClass::getClassDeclare() const noexcept {
	return this->clazz;
}

bool AnalyzedClass::equals(AnalyzedClass* other) noexcept {
	const UnicodeString* sig = getSignatureName();
	const UnicodeString* sig2 = other->getSignatureName();

	return sig->equals(sig2);
}


bool AnalyzedClass::hasBaseClass(AnalyzedClass* clazz) noexcept {
	if(equals(clazz)){
		return true;
	}

	bool result = false;
	if(this->extends != nullptr && this->extends->hasBaseClass(clazz)){
		return true;
	}

	int maxLoop = this->implements.size();
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedClass* impl = this->implements.get(i);

		if(impl->hasBaseClass(clazz)){
			return true;
		}
	}

	return false;
}

void AnalyzedClass::setFactory(IVmInstanceFactory* factory) noexcept {
	this->factory = factory;
}

IVmInstanceFactory* AnalyzedClass::getFactory() const noexcept {
	return this->factory;
}

} /* namespace alinous */
