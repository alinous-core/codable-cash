/*
 * ExtArrayObject.cpp
 *
 *  Created on: 2020/02/18
 *      Author: iizuka
 */

#include "ext_binary/ExtArrayObject.h"

#include "instance/VmInstanceTypesConst.h"

namespace alinous {

ExtArrayObject::ExtArrayObject(const UnicodeString* name, int length) : AbstractExtObject(name, VmInstanceTypesConst::INST_ARRAY) {
	this->length = length;
}

ExtArrayObject::~ExtArrayObject() {

}

void ExtArrayObject::addInnerElement(AbstractExtObject* obj) noexcept {
	this->array.addElement(obj);
}

int ExtArrayObject::getLength() const noexcept {
	return this->length;
}

AbstractExtObject* ExtArrayObject::get(int i) const noexcept {
	return this->array.get(i);
}

} /* namespace alinous */
