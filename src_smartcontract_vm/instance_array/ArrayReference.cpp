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

void ArrayReference::substitute(AbstractVmInstance* rightValue,	VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	if(this->instArray != nullptr){
		gc->removeInstanceReference(this, this->instArray);
		this->instArray = nullptr;
	}

	if(rightValue != nullptr && !rightValue->isNull()){
		VmArrayInstance* inst = dynamic_cast<VmArrayInstance*>(rightValue);

		gc->addInstanceReference(this, inst);
		this->instArray = inst;
	}
}

bool ArrayReference::isNull() const noexcept {
	return this->instArray == nullptr;
}

int ArrayReference::valueCompare(IAbstractVmInstanceSubstance* right) {
	if(isNull()){
		return right->instIsNull() ? 0 : -1;
	}
	else if(right->instIsNull()){
		return isNull() ? 0 : 1;
	}

	ArrayReference* objRight = dynamic_cast<ArrayReference*>(right);
	if(objRight == nullptr){
		return -1;
	}

	return this->instArray->valueCompare(objRight->getInstance());
}

AbstractExtObject* ArrayReference::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return this->instArray->toClassExtObject(name, table);
}

} /* namespace alinous */
