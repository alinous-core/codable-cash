/*
 * VmRootReference.cpp
 *
 *  Created on: 2019/07/08
 *      Author: iizuka
 */

#include "instance_ref/VmRootReference.h"
#include "instance_gc/GcManager.h"
#include "instance_ref_static/StaticInstanceHolder.h"

#include "vm/VirtualMachine.h"


namespace alinous {

VmRootReference::VmRootReference(VirtualMachine* vm) : AbstractReference(AbstractVmInstance::REF_ROOT) {
	this->vm = vm;
	this->mainInst = nullptr;
	this->staticHolder = new StaticInstanceHolder();
}

VmRootReference::~VmRootReference() {
	if(this->mainInst != nullptr){
		GcManager* gc = this->vm->getGc();
		gc->removeInstanceReference(this, this->mainInst);
		this->mainInst = nullptr;
	}

	delete this->staticHolder;
}

void VmRootReference::setMainInstance(AbstractVmInstance* mainInst) noexcept {
	this->mainInst = mainInst;

	GcManager* gc = this->vm->getGc();
	gc->addInstanceReference(this, this->mainInst);
}

} /* namespace alinous */
