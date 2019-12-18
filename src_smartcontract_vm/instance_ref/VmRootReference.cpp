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

#include "instance_ref/RefereceFactory.h"
#include "instance/VmClassInstance.h"

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

		this->staticHolder->removeInnerReferences(this, this->vm);
	}

	delete this->staticHolder;
}

void VmRootReference::setMainInstance(VmClassInstance* mainInst) noexcept {
	this->mainInst = mainInst;

	GcManager* gc = this->vm->getGc();
	gc->addInstanceReference(this, this->mainInst);
}


AbstractVmInstance* VmRootReference::getInstance() noexcept {
	return this->mainInst;
}


PrimitiveReference* VmRootReference::newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm) {
	return this->staticHolder->newNumericConstReferenece(value, type ,vm);
}


} /* namespace alinous */
