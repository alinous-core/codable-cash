/*
 * DomArrayVariable.cpp
 *
 *  Created on: 2020/07/02
 *      Author: iizuka
 */

#include "instance/instance_dom/DomArrayVariable.h"
#include "instance/instance_dom/DomVariableReference.h"

#include "instance/VmInstanceTypesConst.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/AbstractReference.h"

#include "instance/instance_gc/GcManager.h"

#include "ext_binary/ExtDomArrayObject.h"

#include "base/UnicodeString.h"

#include "instance/instance_dom/DomRuntimeReference.h"

namespace alinous {

const UnicodeString DomArrayVariable::LENGTH(L"length");

DomArrayVariable::DomArrayVariable(VirtualMachine* vm) : AbstractDomInstance(vm, VmInstanceTypesConst::INST_DOM_ARRAY), list(vm, 1) {
	this->array = new(vm) VMemList<DomRuntimeReference>(vm);
	this->str = nullptr;
}

DomArrayVariable::~DomArrayVariable() {
	this->array->deleteElements();
	delete this->array;

	delete this->str;
}

IAbstractVmInstanceSubstance* DomArrayVariable::getInstance() noexcept {
	return this;
}

AbstractReference* DomArrayVariable::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	DomVariableReference* ref = new(vm) DomVariableReference(owner, vm, this);

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
		DomRuntimeReference* refref = this->array->get(i);
	//	AbstractReference* ref = refref->getInnerReference();

		gc->removeObject(refref);
		refref->resetOnGc();
	}

	this->array->deleteElements();
	this->array->reset();
}

const VMemList<AbstractReference>* DomArrayVariable::getReferences() const noexcept {
	this->list.reset();

	int maxLoop = this->array->size();
	for(int i = 0; i != maxLoop; ++i){
		DomRuntimeReference* ref = this->array->get(i);

		this->list.addElement(ref);
	}

	return &this->list;
}

AbstractExtObject* DomArrayVariable::toClassExtObject(const UnicodeString* name, VTableRegistory* reg) {
	ExtDomArrayObject* exobj = new ExtDomArrayObject(name);

	int maxLoop = this->array->size();
	for(int i = 0; i != maxLoop; ++i){
		DomRuntimeReference* ref = this->array->get(i);

		AbstractExtObject* obj = ref->toClassExtObject(name, reg);
		exobj->add(obj);
	}

	return exobj;
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
	if(this->str == nullptr){
		this->str = new UnicodeString(L"[");

		int maxLoop = this->array->size();
		for(int i = 0; i != maxLoop; ++i){
			DomRuntimeReference* ref = this->array->get(i);

			if(i != 0){
				this->str->append(L", ");
			}

			if(ref != nullptr && !ref->isNull()){
				const UnicodeString* refstr = ref->toString();
				this->str->append(refstr);
			}
			else {
				this->str->append(&AbstractReference::NULL_STR);
			}
		}

		this->str->append(L"]");
	}

	return this->str;
}

int DomArrayVariable::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	const DomArrayVariable* inst = dynamic_cast<const DomArrayVariable*>(right);

	int64_t diff = ((int64_t)this) - ((int64_t)inst);
	if(diff == 0){
		return 0;
	}

	return diff > 0 ? 1 : -1;
}

void DomArrayVariable::add(VirtualMachine* vm, IAbstractVmInstanceSubstance* inst) {
	DomRuntimeReference* rr = new(vm) DomRuntimeReference(this, vm);

	if(inst == nullptr){
		this->array->addElement(rr);
		return;
	}

	GcManager* gc = vm->getGc();
	rr->substitute(inst, vm);

	this->array->addElement(rr);
}


int DomArrayVariable::size() const noexcept {
	return this->array->size();
}

DomRuntimeReference* DomArrayVariable::get(int i) const noexcept {
	return this->array->get(i);
}

} /* namespace alinous */
