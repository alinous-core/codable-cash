/*
 * DomVariableInstance.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "instance_dom/DomVariableInstance.h"
#include "instance_dom/DomVariableReference.h"

#include "instance/VmInstanceTypesConst.h"

#include "instance_gc/GcManager.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_parts/VMemList.h"

#include "instance_ref/AbstractReference.h"

namespace alinous {

DomVariableInstance::DomVariableInstance(VirtualMachine* vm) : AbstractVmInstance(VmInstanceTypesConst::INST_DOM) {
	this->valueRef = nullptr;
	this->properties = new(vm) VMemList<AbstractReference>(vm);
}

DomVariableInstance::~DomVariableInstance() {
	delete this->properties;
}

void DomVariableInstance::removeInnerRefs(GcManager* gc) noexcept {
	if(this->valueRef != nullptr){
		gc->removeObject(this->valueRef);
		this->valueRef = nullptr;
	}


}

IAbstractVmInstanceSubstance* DomVariableInstance::getInstance() noexcept {
	return this;
}

AbstractReference* DomVariableInstance::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {

}

uint8_t DomVariableInstance::getInstType() const noexcept {
	return getType();
}

AnalyzedType DomVariableInstance::getRuntimeType() const noexcept {
}

const VMemList<AbstractReference>* DomVariableInstance::getReferences() const noexcept {
}

AbstractExtObject* DomVariableInstance::toClassExtObject(const UnicodeString* name, VTableRegistory* reg) {
}

const VMemList<AbstractReference>* DomVariableInstance::getInstReferences() const noexcept {
}

int DomVariableInstance::instHashCode() const noexcept {
}

bool DomVariableInstance::instIsPrimitive() const noexcept {
	return false;
}

bool DomVariableInstance::instIsNull() const noexcept {
	return isNull();
}

int DomVariableInstance::instValueCompare(IAbstractVmInstanceSubstance* right) {
	return valueCompare(right);
}

AbstractExtObject* DomVariableInstance::instToClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return toClassExtObject(name, table);
}

const UnicodeString* DomVariableInstance::toString() noexcept {
	return nullptr;
}

int DomVariableInstance::valueCompare(IAbstractVmInstanceSubstance* right) {
	DomVariableInstance* inst = dynamic_cast<DomVariableInstance*>(right);

	int64_t diff = ((int64_t)this) - ((int64_t)inst);
	if(diff == 0){
		return 0;
	}

	return diff > 0 ? 1 : -1;
}


} /* namespace alinous */
