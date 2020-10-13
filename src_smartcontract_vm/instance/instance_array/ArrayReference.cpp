/*
 * ArrayReference.cpp
 *
 *  Created on: 2020/02/15
 *      Author: iizuka
 */

#include "instance/instance_array/ArrayReference.h"
#include "instance/instance_array/VmArrayInstance.h"

#include "instance/AbstractVmInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance/instance_gc/GcManager.h"

#include "ext_binary/ExtNullPtrObject.h"

namespace alinous {

ArrayReference::ArrayReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) : AbstractReference(owner, VmInstanceTypesConst::REF_ARRAY) {
	this->instArray = nullptr;
}


ArrayReference::ArrayReference(IAbstractVmInstanceSubstance* owner,	VirtualMachine* vm, VmArrayInstance* instArray)
					: AbstractReference(owner, VmInstanceTypesConst::REF_ARRAY){
	this->instArray = instArray;
}

ArrayReference::~ArrayReference() {
	this->instArray = nullptr;
}

IAbstractVmInstanceSubstance* ArrayReference::getInstance() noexcept {
	return this->instArray;
}

void ArrayReference::substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	if(this->instArray != nullptr){
		gc->removeObject(this);
		this->instArray = nullptr;
	}

	if(rightValue != nullptr && !rightValue->instIsNull()){
		VmArrayInstance* inst = dynamic_cast<VmArrayInstance*>(rightValue);

		this->instArray = inst;
		gc->registerObject(this);
	}
}

bool ArrayReference::isNull() const noexcept {
	return this->instArray == nullptr;
}

int ArrayReference::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	if(isNull()){
		return right == nullptr ? 0 : -1;
	}
	else if(right == nullptr){
		return isNull() ? 0 : 1;
	}

	const VmArrayInstance* objRight = dynamic_cast<const VmArrayInstance*>(right);
	if(objRight == nullptr){
		return -1;
	}

	return this->instArray->valueCompare(objRight);
}

AbstractExtObject* ArrayReference::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return this->instArray != nullptr
			? this->instArray->instToClassExtObject(name, table)
			: new ExtNullPtrObject(name, VmInstanceTypesConst::INST_ARRAY);
}

void ArrayReference::resetOnGc() noexcept {
	this->instArray = nullptr;
}

const UnicodeString* ArrayReference::toString() const noexcept {
	return isNull() ? AbstractReference::toString() : this->instArray->toString();
}

} /* namespace alinous */
