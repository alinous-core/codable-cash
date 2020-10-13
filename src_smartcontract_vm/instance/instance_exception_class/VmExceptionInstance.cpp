/*
 * VmExceptionInstance.cpp
 *
 *  Created on: 2020/04/14
 *      Author: iizuka
 */

#include "instance/instance_exception_class/VmExceptionInstance.h"

#include "instance/VmInstanceTypesConst.h"

#include "ext_binary/ExtExceptionObject.h"

#include "engine/sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"

namespace alinous {

VmExceptionInstance::VmExceptionInstance(AnalyzedClass* clazz, VirtualMachine* vm)
				: VmClassInstance(VmInstanceTypesConst::INST_EXCEPTION, clazz, vm) {
	this->element = nullptr;
	this->message = nullptr;
}

VmExceptionInstance::~VmExceptionInstance() {
	this->element = nullptr;
	delete this->message;
}

void VmExceptionInstance::setCodeElement(const CodeElement* element) noexcept {
	this->element = element;
}

const CodeElement* VmExceptionInstance::getElement() const noexcept {
	return this->element;
}

void VmExceptionInstance::setMessage(const UnicodeString* message) noexcept {
	this->message = new UnicodeString(message);
}

AbstractExtObject* VmExceptionInstance::toClassExtObject(const UnicodeString* name, VTableRegistory* reg) {
	ExtExceptionObject* extObj = new ExtExceptionObject(name);
	extObj->setCodeElement(getElement());
	extObj->setClassName(this->clazz->getFullQualifiedName());

	return extObj;
}

const UnicodeString* VmExceptionInstance::toString() noexcept {
	return this->message;
}

} /* namespace alinous */
