/*
 * DomVariableReference.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "instance_dom/DomVariableReference.h"
#include "instance_dom/DomVariableInstance.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "vm/VirtualMachine.h"

namespace alinous {

DomVariableReference::DomVariableReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm)
			: AbstractReference(owner, VmInstanceTypesConst::REF_DOM) {
	this->inst = nullptr;
}

DomVariableReference::~DomVariableReference() {

}

IAbstractVmInstanceSubstance* DomVariableReference::getInstance() noexcept {
	return this->inst;
}

void DomVariableReference::substitute(IAbstractVmInstanceSubstance* rightValue, GcManager* gc) {
}

bool DomVariableReference::isNull() const noexcept {
	return this->inst == nullptr;
}

int DomVariableReference::valueCompare(const IAbstractVmInstanceSubstance* right) {
	if(isNull()){
		return right == nullptr ? 0 : -1;
	}
	else if(right == nullptr){
		return isNull() ? 0 : 1;
	}

	const DomVariableInstance* objRight = dynamic_cast<const DomVariableInstance*>(right);
	if(objRight == nullptr){
		return -1;
	}

	return this->inst->valueCompare(objRight);
}

AbstractExtObject* DomVariableReference::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return isNull() ? nullptr : this->inst->toClassExtObject(name, table);
}

const UnicodeString* DomVariableReference::toString() noexcept {
	return isNull() ? &AbstractReference::NULL_STR : toString();
}

int DomVariableReference::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	if(isNull()){
		return right == nullptr ? 0 : -1;
	}
	else if(right == nullptr){
		return isNull() ? 0 : 1;
	}

	return this->inst->instValueCompare(right);
}

} /* namespace alinous */
