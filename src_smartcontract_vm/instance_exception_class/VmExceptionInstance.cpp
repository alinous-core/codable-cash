/*
 * VmExceptionInstance.cpp
 *
 *  Created on: 2020/04/14
 *      Author: iizuka
 */

#include "instance_exception_class/VmExceptionInstance.h"

#include "instance/VmInstanceTypesConst.h"

#include "ext_binary/ExtExceptionObject.h"

#include "sc_analyze/AnalyzedClass.h"

namespace alinous {

VmExceptionInstance::VmExceptionInstance(AnalyzedClass* clazz, VirtualMachine* vm)
				: VmClassInstance(VmInstanceTypesConst::INST_EXCEPTION, clazz, vm) {
	this->element = nullptr;
}

VmExceptionInstance::~VmExceptionInstance() {
	this->element = nullptr;
}

void VmExceptionInstance::setCodeElement(const CodeElement* element) noexcept {
	this->element = element;
}

const CodeElement* VmExceptionInstance::getElement() const noexcept {
	return this->element;
}

AbstractExtObject* VmExceptionInstance::toClassExtObject(const UnicodeString* name, VTableRegistory* reg) {
	ExtExceptionObject* extObj = new ExtExceptionObject(name);
	extObj->setCodeElement(getElement());
	extObj->setClassName(this->clazz->getFullQualifiedName());

	return extObj;
}

} /* namespace alinous */
