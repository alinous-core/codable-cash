/*
 * ClassTypeAccess.cpp
 *
 *  Created on: 2020/04/28
 *      Author: iizuka
 */

#include "variable_access/ClassTypeAccess.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/ValidationError.h"

#include "vm/VirtualMachine.h"

#include "instance_ref_class_static/ClassTypeReference.h"

#include "sc/SmartContract.h"

#include "instance_ref/VmRootReference.h"

#include "sc_expression/VariableIdentifier.h"

#include "base/StackRelease.h"


namespace alinous {

ClassTypeAccess::ClassTypeAccess(const AnalyzedType* atype)
		: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_CLASS_TYPE){
	this->atype = new AnalyzedType(*atype);
	this->element = nullptr;
	this->superId = nullptr;
}

ClassTypeAccess::ClassTypeAccess(VariableIdentifier* superId)
		: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_CLASS_TYPE){
	this->atype = nullptr;
	this->element = nullptr;
	this->superId = superId;
}

ClassTypeAccess::~ClassTypeAccess() {
	delete this->atype;
}

void ClassTypeAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	this->element = element;

	if(this->superId != nullptr){
		analyzeSuperId(actx, lastIinst, element);
	}
}

void ClassTypeAccess::analyzeSuperId(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	TypeResolver* resolver = actx->getTypeResolver();

	AnalyzedType* atp = resolver->getClassType(this->superId); __STP(atp);
	AnalyzedClass* clazz = atp->getAnalyzedClass();


	AnalyzedClass* superClazz = clazz->getExtends();
	if(superClazz == nullptr){
		const UnicodeString* name = clazz->getFullQualifiedName();
		actx->addValidationError(ValidationError::CODE_CLASS_MEMBER_DOES_NOT_EXISTS, this->superId, L"The super class of '{0}' does not exists.", {name});
		this->hasError = true;
		return;
	}

	this->atype = new AnalyzedType(new AnalyzedClass(*superClazz));
}

AnalyzedType ClassTypeAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* ClassTypeAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	SmartContract* sc = vm->getSmartContract();
	VmRootReference* root = sc->getRootReference();

	ClassTypeReference* ref = new(vm) ClassTypeReference(root, vm, this->atype);

	return ref;
}

CodeElement* ClassTypeAccess::getCodeElement() const noexcept {
	return this->element;
}

} /* namespace alinous */
