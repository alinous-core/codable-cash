/*
 * VmStringInstance.cpp
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#include "instance/instance_string/VmStringInstance.h"

#include "instance/VmInstanceTypesConst.h"
#include "instance/instance_ref/ObjectReference.h"
#include "instance/instance_string/VmString.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtStringClass.h"

#include "engine/sc_analyze/AnalyzedType.h"

namespace alinous {

const VmString::ValueCompare VmStringInstance::compareFunctor;

VmStringInstance::VmStringInstance(VirtualMachine* vm, const UnicodeString* str) : AbstractVmInstance(VmInstanceTypesConst::INST_STRING) {
	this->value = new(vm) VmString(vm, str);
	this->str = nullptr;
}

int VmStringInstance::hashCode() const noexcept {
	return this->value->hashCode();
}

VmStringInstance* VmStringInstance::copy(VirtualMachine* vm) const {
	UnicodeString str(this->value->towString());

	return new(vm) VmStringInstance(vm, &str);
}

VmStringInstance::~VmStringInstance() {
	delete this->value;
	delete this->str;
}

int VmStringInstance::valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	const VmStringInstance* rightStr = dynamic_cast<const VmStringInstance*>(right);

	return compareFunctor(this->value, rightStr->value);
}

IAbstractVmInstanceSubstance* VmStringInstance::getInstance() noexcept {
	return this;
}

AbstractReference* VmStringInstance::wrap(IAbstractVmInstanceSubstance* owner,	VirtualMachine* vm) {
	return ObjectReference::createStringReference(owner, this, vm);
}

uint8_t VmStringInstance::getInstType() const noexcept {
	return getType();
}

const VMemList<AbstractReference>* VmStringInstance::getInstReferences() const noexcept {
	return getReferences();
}

int VmStringInstance::instHashCode() const noexcept {
	return hashCode();
}

bool VmStringInstance::instIsNull() const noexcept {
	return isNull();
}

int VmStringInstance::instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept {
	return valueCompare(right);
}

AbstractExtObject* VmStringInstance::instToClassExtObject(
		const UnicodeString* name, VTableRegistory* table) {
	return toClassExtObject(name, table);
}

bool VmStringInstance::instIsPrimitive() const noexcept {
	return false;
}

AnalyzedType VmStringInstance::getRuntimeType() const noexcept {
	return AnalyzedType(AnalyzedType::TYPE_STRING);
}

AbstractExtObject* VmStringInstance::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	const wchar_t* wchar_str = this->value->towString();
	UnicodeString str(wchar_str);

	return new ExtStringClass(name, &str);
}

const UnicodeString* VmStringInstance::toString() const noexcept {
	delete this->str;
	this->str = new UnicodeString(this->value->towString());

	return this->str;
}

int VmStringInstance::ValueCompare::operator ()(
		const VmStringInstance* const _this, const VmStringInstance* const object) const noexcept {
	return VmStringInstance::compareFunctor(_this->value, object->value);
}


} /* namespace alinous */
