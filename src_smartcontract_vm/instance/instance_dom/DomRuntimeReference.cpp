/*
 * DomRuntimeReference.cpp
 *
 *  Created on: 2020/06/27
 *      Author: iizuka
 */

#include "instance/instance_dom/DomRuntimeReference.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "vm/VirtualMachine.h"

#include "ext_binary/ExtNullPtrObject.h"

#include "instance/instance_gc/GcManager.h"
namespace alinous {

DomRuntimeReference::DomRuntimeReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm)
		: AbstractReference(owner, VmInstanceTypesConst::REF_DOM_RUNTIME){
	this->reference = nullptr;
}

DomRuntimeReference::~DomRuntimeReference() {
	delete this->reference;
}

bool DomRuntimeReference::isPrimitive() const noexcept {
	return this->reference == nullptr ? false : this->reference->isPrimitive();
}

IAbstractVmInstanceSubstance* DomRuntimeReference::getInstance() noexcept {
	return this->reference == nullptr ? nullptr : this->reference->getInstance();
}

void DomRuntimeReference::substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	if(this->reference != nullptr && !this->reference->isNull()){
		gc->removeObject(this);
		delete this->reference;
		this->reference = nullptr;
	}

	if(rightValue != nullptr && !rightValue->instIsNull()){
		this->reference = rightValue->wrap(this->owner, vm);
		gc->registerObject(this);
	}
	else {
		this->reference = nullptr;
	}
}

bool DomRuntimeReference::isNull() const noexcept {
	return this->reference == nullptr ? true : this->reference->isNull();
}

void DomRuntimeReference::resetOnGc() noexcept {
	if(this->reference != nullptr){
		this->reference->resetOnGc();

		delete this->reference;
		this->reference = nullptr;
	}
}

int DomRuntimeReference::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	if(isNull()){
		return right == nullptr ? 0 : -1;
	}
	else if(right == nullptr){
		return isNull() ? 0 : 1;
	}

	return this->reference->valueCompare(right);
}

AbstractExtObject* DomRuntimeReference::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return this->reference == nullptr ? new ExtNullPtrObject(name, VmInstanceTypesConst::REF_DOM_RUNTIME) : this->reference->toClassExtObject(name, table);
}

const UnicodeString* DomRuntimeReference::toString() const noexcept {
	return this->reference == nullptr ? &AbstractReference::NULL_STR : this->reference->toString();
}

} /* namespace alinous */
