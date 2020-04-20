/*
 * ArrayReference.cpp
 *
 *  Created on: 2020/02/15
 *      Author: iizuka
 */

#include "instance_array/ArrayReference.h"
#include "instance_array/VmArrayInstance.h"

#include "instance/AbstractVmInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance_gc/GcManager.h"

#include "ext_binary/ExtNullPtrObject.h"

namespace alinous {

ArrayReference::ArrayReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) : AbstractReference(owner, VmInstanceTypesConst::REF_ARRAY) {
	this->instArray = nullptr;
}

ArrayReference::~ArrayReference() {
	this->instArray = nullptr;
}

IAbstractVmInstanceSubstance* ArrayReference::getInstance() noexcept {
	return this->instArray;
}

void ArrayReference::substitute(IAbstractVmInstanceSubstance* rightValue,	VirtualMachine* vm) {
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

int ArrayReference::valueCompare(IAbstractVmInstanceSubstance* right) {
	if(isNull()){
		return right == nullptr ? 0 : -1;
	}
	else if(right == nullptr){
		return isNull() ? 0 : 1;
	}

	VmArrayInstance* objRight = dynamic_cast<VmArrayInstance*>(right);
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

} /* namespace alinous */
