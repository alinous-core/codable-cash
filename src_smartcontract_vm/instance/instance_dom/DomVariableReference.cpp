/*
 * DomVariableReference.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "instance/instance_dom/DomVariableReference.h"
#include "instance/instance_dom/DomVariableInstance.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_gc/GcManager.h"

#include "instance/instance_dom/AbstractDomInstance.h"

namespace alinous {

DomVariableReference::DomVariableReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm, AbstractDomInstance* inst)
			: AbstractReference(owner, VmInstanceTypesConst::REF_DOM) {
	this->inst = inst;
}

DomVariableReference::~DomVariableReference() {

}

IAbstractVmInstanceSubstance* DomVariableReference::getInstance() noexcept {
	return this->inst;
}

void DomVariableReference::substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	if(this->inst != nullptr){
		gc->removeObject(this);
		this->inst = nullptr;
	}

	if(rightValue != nullptr && !rightValue->instIsNull()){
		this->inst = dynamic_cast<AbstractDomInstance*>(rightValue);
		gc->registerObject(this);
	}
	else {
		this->inst = nullptr;
	}
}

bool DomVariableReference::isNull() const noexcept {
	return this->inst == nullptr;
}

AbstractExtObject* DomVariableReference::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return isNull() ? nullptr : this->inst->toClassExtObject(name, table);
}

const UnicodeString* DomVariableReference::toString() const noexcept {
	return isNull() ? &AbstractReference::NULL_STR : this->inst->toString();
}

void DomVariableReference::resetOnGc() noexcept {
	this->inst = nullptr;
}

bool DomVariableReference::isDom() const noexcept {
	return true;
}

int DomVariableReference::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	if(isNull()){
		return right == nullptr ? 0 : -1;
	}
	else if(right == nullptr){
		return isNull() ? 0 : 1;
	}

	const AbstractDomInstance* objRight = dynamic_cast<const AbstractDomInstance*>(right);
	if(objRight == nullptr){
		return -1;
	}

	return this->inst->valueCompare(objRight);
}

} /* namespace alinous */
