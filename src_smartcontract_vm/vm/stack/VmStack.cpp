/*
 * VmStack.cpp
 *
 *  Created on: 2019/06/30
 *      Author: iizuka
 */

#include "vm/stack/VmStack.h"

#include "instance/instance_ref/AbstractReference.h"
#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/AbstractVmInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "engine/sc_analyze/AnalyzedType.h"

namespace alinous {

VmStack::VmStack(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm)
				: AbstractReference(owner, VmInstanceTypesConst::STACK), IInstanceContainer() {
	this->stack = new(vm) VMemList<AbstractReference>(vm);
	this->vm = vm;
}

VmStack::~VmStack() {
	delete this->stack;
}

void VmStack::addInnerReference(AbstractReference* ref) {
	GcManager* gc = vm->getGc();

	if(ref->isPrimitive()){
		PrimitiveReference* pref = dynamic_cast<PrimitiveReference*>(ref);

		//pref = pref->copy(vm);
		pref->setOwner(this);
		this->stack->addElement(pref);

		return;
	}

	this->stack->addElement(ref);

	gc->registerObject(ref);
}

const VMemList<AbstractReference>* VmStack::getReferences() const noexcept {
	return this->stack;
}

void VmStack::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->stack->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->stack->get(i);

		if(!ref->isPrimitive()){
			gc->removeObject(ref);
			ref->resetOnGc();
		}

		delete ref;
	}

	this->stack->reset();
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

int VmStack::instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	return valueCompare(right);
}

AbstractExtObject* VmStack::instToClassExtObject(const UnicodeString* name,	VTableRegistory* table) {
	return toClassExtObject(name, table);
}

bool VmStack::instIsPrimitive() const noexcept {
	return false;
}

IAbstractVmInstanceSubstance* VmStack::getInstance() noexcept {
	return this;
}

int VmStack::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	return 0;
}

AnalyzedType VmStack::getRuntimeType() const noexcept {
	return AnalyzedType();
}

void VmStack::resetOnGc() noexcept {
	this->stack->reset();
}

} /* namespace alinous */
