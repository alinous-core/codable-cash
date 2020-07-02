/*
 * DomArrayVariable.cpp
 *
 *  Created on: 2020/07/02
 *      Author: iizuka
 */

#include "instance_dom/DomArrayVariable.h"

#include "instance/VmInstanceTypesConst.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

DomArrayVariable::DomArrayVariable(VirtualMachine* vm) : AbstractDomInstance(vm, VmInstanceTypesConst::INST_DOM_ARRAY) {

}

DomArrayVariable::~DomArrayVariable() {

}

IAbstractVmInstanceSubstance* DomArrayVariable::getInstance() noexcept {
	return this;
}

AbstractReference* DomArrayVariable::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
}

uint8_t DomArrayVariable::getInstType() const noexcept {
	return getType();
}

AnalyzedType DomArrayVariable::getRuntimeType() const noexcept {
	return AnalyzedType(AnalyzedType::TYPE_DOM_ARRAY);
}

void DomArrayVariable::removeInnerRefs(GcManager* gc) noexcept {
}

const VMemList<AbstractReference>* DomArrayVariable::getReferences() const noexcept {
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
}

const UnicodeString* DomArrayVariable::toString() const noexcept {
}

int DomArrayVariable::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {

}

} /* namespace alinous */
