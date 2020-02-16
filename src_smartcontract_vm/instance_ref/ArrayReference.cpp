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
	this->array = new(vm) VMemList<AbstractVmInstance>(vm);
}

ArrayReference::~ArrayReference() {
	delete this->array;
}

void ArrayReference::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->array->size();

	for(int i = 0; i != maxLoop; ++i){
		AbstractVmInstance* ref = this->array->get(i);

		// remove ref
		//gc->removeRefReference(this, ref);
	}
}

void ArrayReference::add(AbstractVmInstance* inst) {
	this->array->addElement(inst);
}

} /* namespace alinous */
