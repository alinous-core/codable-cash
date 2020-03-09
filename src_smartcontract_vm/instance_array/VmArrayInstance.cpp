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

#include "ext_binary/ExtArrayObject.h"

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
	ExtArrayObject* obj = new ExtArrayObject(name, this->length);

	int maxLoop = this->array->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->array->get(i);
		AbstractExtObject* innerObj = ref->toClassExtObject(name, reg);

		obj->addInnerElement(innerObj);
	}

	return obj;
}

int VmArrayInstance::valueCompare(const AbstractVmInstance* right) const {
	// FIXME compare
}

void VmArrayInstance::setReference(VirtualMachine* vm, int pos, AbstractReference* ref) noexcept {
	GcManager* gc = vm->getGc();

	AbstractReference* last = this->array->get(pos);
	if(last != nullptr){
		gc->removeRefReference(this, last);
	}

	if(ref != nullptr){
		gc->addRefReference(this, ref);
		this->array->setElement(ref, pos);
	}

}

} /* namespace alinous */
