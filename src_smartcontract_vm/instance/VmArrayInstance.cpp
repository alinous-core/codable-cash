/*
 * VmArrayInstance.cpp
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#include "instance/VmArrayInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance_gc/GcManager.h"

#include "instance_ref/AbstractReference.h"


namespace alinous {

VmArrayInstance::VmArrayInstance(VirtualMachine* vm) : AbstractVmInstance(VmInstanceTypesConst::INST_ARRAY) {
	this->array = new(vm) VMemList<AbstractReference>(vm);

}

VmArrayInstance::~VmArrayInstance() {
	this->array->deleteElements();
	delete this->array;
}

void VmArrayInstance::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->array->size();

	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->array->get(i);

		// remove ref
		gc->removeRefReference(this, ref);
	}
}

} /* namespace alinous */
