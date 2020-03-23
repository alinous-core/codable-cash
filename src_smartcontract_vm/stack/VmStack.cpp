/*
 * VmStack.cpp
 *
 *  Created on: 2019/06/30
 *      Author: iizuka
 */

#include "stack/VmStack.h"

#include "instance_ref/AbstractReference.h"

#include "instance_gc/GcManager.h"
#include "instance/AbstractVmInstance.h"
#include "instance/VmInstanceTypesConst.h"


namespace alinous {

VmStack::VmStack(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm)
				: AbstractReference(VmInstanceTypesConst::STACK), IInstanceContainer(owner) {
	this->stack = new(vm) VMemList<AbstractReference>(vm);
	this->vm = vm;
}

VmStack::~VmStack() {
	delete this->stack;
}

void VmStack::addInnerReference(AbstractReference* ref) {
	GcManager* gc = vm->getGc();

	this->stack->addElement(ref);

	AbstractVmInstance* inst = nullptr;
	if(ref->isPrimitive()){
		return;
	}
	else{
		inst = ref->getInstance();
	}

	gc->addInstanceReference(this, inst);
}

const VMemList<AbstractReference>* VmStack::getReferences() const noexcept {
	return this->stack;
}

void VmStack::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->stack->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->stack->get(i);

		gc->removeObject(ref);

		delete ref;
	}
}


AbstractReference* VmStack::get(int pos) const noexcept {
	return this->stack->get(pos);
}

AbstractReference* VmStack::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	return this;
}

uint8_t VmStack::getInstType() const noexcept {
	return getType();
}

const VMemList<AbstractReference>* VmStack::getInstReferences() const noexcept {
	return getReferences();
}

int VmStack::instHashCode() const noexcept {
	return hashCode();
}

bool VmStack::instIsNull() const noexcept {
	return isNull();
}

int VmStack::instValueCompare(IAbstractVmInstanceSubstance* right) {
	return valueCompare(right);
}

AbstractExtObject* VmStack::instToClassExtObject(const UnicodeString* name,	VTableRegistory* table) {
	return toClassExtObject(name, table);
}

bool VmStack::instIsPrimitive() const noexcept {
	return false;
}

int VmStack::valueCompare(IAbstractVmInstanceSubstance* right) {
	return 0;
}



} /* namespace alinous */
