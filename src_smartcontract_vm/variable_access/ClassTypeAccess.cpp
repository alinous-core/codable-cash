/*
 * ClassTypeAccess.cpp
 *
 *  Created on: 2020/04/28
 *      Author: iizuka
 */

#include "variable_access/ClassTypeAccess.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "vm/VirtualMachine.h"

#include "instance_ref_class_static/ClassTypeReference.h"

#include "sc/SmartContract.h"

#include "instance_ref/VmRootReference.h"


namespace alinous {

ClassTypeAccess::ClassTypeAccess(const AnalyzedType* atype)
		: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_CLASS_TYPE){
	this->atype = new AnalyzedType(*atype);
	this->element = nullptr;
}

ClassTypeAccess::~ClassTypeAccess() {
	delete this->atype;
}

void ClassTypeAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	this->element = element;
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
