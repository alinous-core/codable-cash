/*
 * ExtArrayObject.cpp
 *
 *  Created on: 2020/02/18
 *      Author: iizuka
 */

#include "ext_binary/ExtArrayObject.h"

#include "instance/VmInstanceTypesConst.h"

namespace alinous {

ExtArrayObject::ExtArrayObject(const UnicodeString* name, int dim) : AbstractExtObject(name, VmInstanceTypesConst::INST_ARRAY) {
	this->dim = dim;
}

ExtArrayObject::~ExtArrayObject() {

}

void ExtArrayObject::addInnerElement(AbstractExtObject* obj) noexcept {
	this->array.addElement(obj);
}


} /* namespace alinous */
