/*
 * DomVariableInstance.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "instance_dom/DomVariableInstance.h"
#include "instance_dom/DomVariableReference.h"
#include "instance_dom/DomRuntimeReference.h"

#include "instance/VmInstanceTypesConst.h"

#include "instance_gc/GcManager.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_parts/VMemList.h"

#include "instance_ref/AbstractReference.h"

#include "ext_binary/ExtDomObject.h"


namespace alinous {

DomVariableInstance::DomVariableInstance(VirtualMachine* vm) : AbstractDomInstance(vm, VmInstanceTypesConst::INST_DOM) {
	this->valueRef = nullptr;
	this->properties = new(vm) VMemHashmap<VmStringInstance, DomRuntimeReference>(vm);
	this->list = nullptr;
}

DomVariableInstance::~DomVariableInstance() {
	delete this->properties;
	delete this->list;
}

void DomVariableInstance::removeInnerRefs(GcManager* gc) noexcept {
	if(this->valueRef != nullptr){
		gc->removeObject(this->valueRef);
		this->valueRef = nullptr;
	}

	Iterator<VmStringInstance>* it = this->properties->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const VmStringInstance* key = it->next();
		DomRuntimeReference* ref = this->properties->get(key);

		gc->removeObject(ref);
	}

	this->properties->clear();
}

IAbstractVmInstanceSubstance* DomVariableInstance::getInstance() noexcept {
	return this;
}

AbstractReference* DomVariableInstance::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	DomVariableReference* ref = new(vm) DomVariableReference(owner, vm);
	ref->substitute(this, vm->getGc());

	return ref;
}

uint8_t DomVariableInstance::getInstType() const noexcept {
	return getType();
}

AnalyzedType DomVariableInstance::getRuntimeType() const noexcept {
	return AnalyzedType(AnalyzedType::TYPE_DOM);
}

const VMemList<AbstractReference>* DomVariableInstance::getReferences() const noexcept {
	if(this->list == nullptr){

		Iterator<VmStringInstance>* it = this->properties->keySet()->iterator(); __STP(it);
		while(it->hasNext()){
			const VmStringInstance* key = it->next();
			DomRuntimeReference* ref = this->properties->get(key);

			this->list->addElement(ref);
		}
	}

	return this->list;
}

AbstractExtObject* DomVariableInstance::toClassExtObject(const UnicodeString* name, VTableRegistory* reg) {
	ExtDomObject* domExobj = new ExtDomObject(name);

	Iterator<VmStringInstance>* it = this->properties->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const VmStringInstance* key = it->next();
		DomRuntimeReference* ref = this->properties->get(key);

		const UnicodeString* keyStr = key->toString();
		AbstractExtObject* exobj = ref->toClassExtObject(keyStr, reg);

		domExobj->put(keyStr, exobj);
	}

	return domExobj;
}

const VMemList<AbstractReference>* DomVariableInstance::getInstReferences() const noexcept {
	return getReferences();
}

int DomVariableInstance::instHashCode() const noexcept {
	return hashCode();
}

bool DomVariableInstance::instIsPrimitive() const noexcept {
	return false;
}

bool DomVariableInstance::instIsNull() const noexcept {
	return isNull();
}

int DomVariableInstance::instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	return valueCompare(right);
}

AbstractExtObject* DomVariableInstance::instToClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return toClassExtObject(name, table);
}

const UnicodeString* DomVariableInstance::toString() const noexcept {
	return nullptr;
}

int DomVariableInstance::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	const DomVariableInstance* inst = dynamic_cast<const DomVariableInstance*>(right);

	int64_t diff = ((int64_t)this) - ((int64_t)inst);
	if(diff == 0){
		return 0;
	}

	return diff > 0 ? 1 : -1;
}

void DomVariableInstance::putProperty(VirtualMachine* vm, VmStringInstance* key, DomRuntimeReference* rr) noexcept {
	GcManager* gc = vm->getGc();

	rr->setOwner(this);
	gc->registerObject(rr);

	DomRuntimeReference* lastrr = this->properties->put(key, rr);
	if(lastrr != nullptr){
		gc->removeObject(lastrr);
		delete lastrr;
	}
}

} /* namespace alinous */
