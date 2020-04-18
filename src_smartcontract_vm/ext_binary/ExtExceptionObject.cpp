/*
 * ExtExceptionObject.cpp
 *
 *  Created on: 2020/04/16
 *      Author: iizuka
 */

#include "ext_binary/ExtExceptionObject.h"

#include "instance/VmInstanceTypesConst.h"
namespace alinous {

ExtExceptionObject::ExtExceptionObject(const UnicodeString* name) : AbstractExtObject(name, VmInstanceTypesConst::INST_EXCEPTION) {
	this->element = nullptr;
}

ExtExceptionObject::~ExtExceptionObject() {
	this->element = nullptr;
}

void ExtExceptionObject::setCodeElement(const CodeElement* element) noexcept {
	this->element = element;
}

const CodeElement* ExtExceptionObject::getCodeElement() const noexcept {
	return this->element;
}

} /* namespace alinous */
