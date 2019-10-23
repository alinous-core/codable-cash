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

namespace alinous {

VmStack::VmStack(VirtualMachine* vm) : AbstractReference(AbstractVmInstance::STACK) {
	this->stack = new(vm) VMemList<AbstractReference>(vm);
	this->vm = vm;
}

VmStack::~VmStack() {
	int maxLoop = this->stack->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->stack->get(i);
		delete ref;
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

	gc->addReference(this, inst);
}

const VMemList<AbstractReference>* VmStack::getReferences() const noexcept {
	return this->stack;
}

void VmStack::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->stack->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->stack->get(i);

		gc->removeReference(this, ref);
	}
}


} /* namespace alinous */
