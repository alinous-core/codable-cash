/*
 * DomArrayVariable.cpp
 *
 *  Created on: 2020/07/02
 *      Author: iizuka
 */

#include "instance_dom/DomArrayVariable.h"
#include "instance_dom/DomVariableReference.h"

#include "instance/VmInstanceTypesConst.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref/AbstractReference.h"

#include "instance_gc/GcManager.h"

namespace alinous {

DomArrayVariable::DomArrayVariable(VirtualMachine* vm) : AbstractDomInstance(vm, VmInstanceTypesConst::INST_DOM_ARRAY) {
	this->array = new(vm) VMemList<AbstractReference>(vm);
}

DomArrayVariable::~DomArrayVariable() {
	this->array->deleteElements();
	delete this->array;
}

IAbstractVmInstanceSubstance* DomArrayVariable::getInstance() noexcept {
	return this;
}

AbstractReference* DomArrayVariable::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	DomVariableReference* ref = new(vm) DomVariableReference(owner, vm);
	ref->substitute(this, vm->getGc());

	return ref;
}

uint8_t DomArrayVariable::getInstType() const noexcept {
	return getType();
}

AnalyzedType DomArrayVariable::getRuntimeType() const noexcept {
	return AnalyzedType(AnalyzedType::TYPE_DOM_ARRAY);
}

void DomArrayVariable::removeInnerRefs(GcManager* gc) noexcept {
	int maxLoop = this->array->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = this->array->get(i);

		gc->removeObject(ref);
	}

	this->array->deleteElements();
	this->array->reset();
}

const VMemList<AbstractReference>* DomArrayVariable::getReferences() const noexcept {
	return this->array;
}

AbstractExtObject* DomArrayVariable::toClassExtObject(const UnicodeString* name, VTableRegistory* reg) {

}

const VMemList<AbstractReference>* DomArrayVariable::getInstReferences() const noexcept {
	return getReferences();
}

int DomArrayVariable::instHashCode() const noexcept {
	return hashCode();
}

bool DomArrayVariable::instIsPrimitive() const noexcept {
	return false;
}

bool DomArrayVariable::instIsNull() const noexcept {
	return isNull();
}

int DomArrayVariable::instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	return valueCompare(right);
}

AbstractExtObject* DomArrayVariable::instToClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return toClassExtObject(name, table);
}

const UnicodeString* DomArrayVariable::toString() const noexcept {
}

int DomArrayVariable::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	const DomArrayVariable* inst = dynamic_cast<const DomArrayVariable*>(right);

	int64_t diff = ((int64_t)this) - ((int64_t)inst);
	if(diff == 0){
		return 0;
	}

	return diff > 0 ? 1 : -1;
}

} /* namespace alinous */
