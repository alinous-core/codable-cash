/*
 * ArrayReference.cpp
 *
 *  Created on: 2020/02/15
 *      Author: iizuka
 */

#include "instance_ref/ArrayReference.h"

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

void ArrayReference::initArray(int dim) {

}

} /* namespace alinous */
