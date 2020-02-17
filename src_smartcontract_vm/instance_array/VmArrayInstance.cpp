/*
 * VmArrayInstance.cpp
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#include "instance_array/VmArrayInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance_gc/GcManager.h"

#include "instance_ref/AbstractReference.h"


namespace alinous {

VmArrayInstance::VmArrayInstance(VirtualMachine* vm, int length) : AbstractVmInstance(VmInstanceTypesConst::INST_ARRAY) {
	this->array = new(vm) VMemList<AbstractReference>(vm);
	this->length = length;

	for(int i = 0; i != length; ++i){
		this->array->addElement(nullptr);
	}

}

VmArrayInstance::~VmArrayInstance() {
	int maxLoop = this->array->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->array->get(i);

		if(ref != nullptr && !ref->isPrimitive()){
			delete ref;
		}
	}

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

const VMemList<AbstractReference>* VmArrayInstance::getReferences() const noexcept {
	return this->array;
}

AbstractExtObject* VmArrayInstance::toClassExtObject(const UnicodeString* name,	VTableRegistory* reg) {
	// FIXME toClassExtObject
	return nullptr;
}

void VmArrayInstance::setReference(int pos, AbstractReference* ref) noexcept {
	this->array->setElement(ref, pos);
}

} /* namespace alinous */
