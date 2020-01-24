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

VmStack::VmStack(VirtualMachine* vm) : AbstractReference(VmInstanceTypesConst::STACK) {
	this->stack = new(vm) VMemList<AbstractReference>(vm);
	this->vm = vm;
}

VmStack::~VmStack() {
	int maxLoop = this->stack->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->stack->get(i);

		if(!ref->isPrimitive()){
			delete ref;
		}
	}

	delete this->stack;
}

void VmStack::addInnerReference(AbstractReference* ref) {
	GcManager* gc = vm->getGc();

	this->stack->addElement(ref);

	AbstractVmInstance* inst = nullptr;
	if(ref->isPrimitive()){
		inst = ref;
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

		gc->removeInstanceReference(this, ref);
	}
}


AbstractReference* VmStack::get(int pos) const noexcept {
	return this->stack->get(pos);
}


} /* namespace alinous */
