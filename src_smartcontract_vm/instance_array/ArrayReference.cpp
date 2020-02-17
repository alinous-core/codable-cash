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

ArrayReference::ArrayReference(VirtualMachine* vm) : AbstractReference(VmInstanceTypesConst::REF_ARRAY) {
	this->instArray = nullptr;
}

ArrayReference::~ArrayReference() {
	this->instArray = nullptr;
}

AbstractVmInstance* ArrayReference::getInstance() noexcept {
	return this->instArray;
}

void ArrayReference::substitute(AbstractVmInstance* rightValue,	VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	if(this->instArray != nullptr){
		gc->removeInstanceReference(this, this->instArray);
		this->instArray = nullptr;
	}

	if(!rightValue->isNull()){
		VmArrayInstance* inst = dynamic_cast<VmArrayInstance*>(rightValue);

		gc->addInstanceReference(this, inst);
		this->instArray = inst;
	}
}

bool ArrayReference::isNull() const noexcept {
	return this->instArray == nullptr;
}


} /* namespace alinous */
