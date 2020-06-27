/*
 * DomRuntimeReference.cpp
 *
 *  Created on: 2020/06/27
 *      Author: iizuka
 */

#include "instance_dom/DomRuntimeReference.h"

#include "instance/IAbstractVmInstanceSubstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "vm/VirtualMachine.h"

#include "ext_binary/ExtNullPtrObject.h"

namespace alinous {

DomRuntimeReference::DomRuntimeReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm)
		: AbstractReference(owner, VmInstanceTypesConst::REF_DOM_RUNTIME){
	this->reference = nullptr;
}

DomRuntimeReference::~DomRuntimeReference() {
}

IAbstractVmInstanceSubstance* DomRuntimeReference::getInstance() noexcept {
	return this->reference == nullptr ? nullptr : this->reference->getInstance();
}

void DomRuntimeReference::substitute(IAbstractVmInstanceSubstance* rightValue, GcManager* gc) {

}

bool DomRuntimeReference::isNull() const noexcept {
	return this->reference == nullptr ? true : this->reference->isNull();
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
