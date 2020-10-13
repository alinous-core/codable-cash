/*
 * ClassTypeReference.cpp
 *
 *  Created on: 2020/04/29
 *      Author: iizuka
 */

#include "instance/instance_ref_class_static/ClassTypeReference.h"

#include "instance/VmInstanceTypesConst.h"
#include "instance/IAbstractVmInstanceSubstance.h"

#include "vm/VirtualMachine.h"

#include "engine/sc_analyze/AnalyzedType.h"


namespace alinous {

ClassTypeReference::ClassTypeReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm, const AnalyzedType* type)
	: AbstractReference(owner, VmInstanceTypesConst::REF_CLASS_TYPE) {
	this->atype = new AnalyzedType(*type);

}

ClassTypeReference::~ClassTypeReference() {
	delete this->atype;
}

IAbstractVmInstanceSubstance* ClassTypeReference::getInstance() noexcept {
	return this;
}

int ClassTypeReference::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	return 0;
}

AbstractReference* ClassTypeReference::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	return nullptr;
}

uint8_t ClassTypeReference::getInstType() const noexcept {
	return getType();
}

AnalyzedType ClassTypeReference::getRuntimeType() const noexcept {
	return *this->atype;
}

const VMemList<AbstractReference>* ClassTypeReference::getInstReferences() const noexcept {
	return nullptr;
}

int ClassTypeReference::instHashCode() const noexcept {
	return 0;
}

bool ClassTypeReference::instIsPrimitive() const noexcept {
	return isPrimitive();
}

bool ClassTypeReference::instIsNull() const noexcept {
	return isNull();
}

int ClassTypeReference::instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	return valueCompare(right);
}

void ClassTypeReference::resetOnGc() noexcept {
}

AbstractExtObject* ClassTypeReference::instToClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return nullptr;
}

} /* namespace alinous */
