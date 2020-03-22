/*
 * VmStringInstance.cpp
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#include "instance_string/VmStringInstance.h"

#include "instance/VmInstanceTypesConst.h"
#include "instance_ref/ObjectReference.h"
#include "instance_string/VmString.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtStringClass.h"


namespace alinous {

const VmString::ValueCompare VmStringInstance::compareFunctor;

VmStringInstance::VmStringInstance(VirtualMachine* vm, const UnicodeString* str) : AbstractVmInstance(VmInstanceTypesConst::INST_STRING) {
	this->value = new(vm) VmString(vm, str);
}

VmStringInstance::~VmStringInstance() {
	delete this->value;
}

int VmStringInstance::valueCompare(IAbstractVmInstanceSubstance* right) {
	VmStringInstance* rightStr = dynamic_cast<VmStringInstance*>(right);

	return compareFunctor(this->value, rightStr->value);
}

IAbstractVmInstanceSubstance* VmStringInstance::getInstance() noexcept {
	return this;
}

AbstractReference* VmStringInstance::wrap(IAbstractVmInstanceSubstance* owner,	VirtualMachine* vm) {
	return ObjectReference::createStringReference(owner, thus, vm);
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

AbstractExtObject* VmStringInstance::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	const wchar_t* wchar_str = this->value->towString();
	UnicodeString str(wchar_str);

	return new ExtStringClass(name, &str);
}

} /* namespace alinous */
