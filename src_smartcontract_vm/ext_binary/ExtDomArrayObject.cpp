/*
 * ExtDomArrayObject.cpp
 *
 *  Created on: 2020/07/02
 *      Author: iizuka
 */

#include "ext_binary/ExtDomArrayObject.h"

#include "instance/VmInstanceTypesConst.h"

namespace alinous {

ExtDomArrayObject::ExtDomArrayObject() : AbstractExtObject(name, VmInstanceTypesConst::INST_DOM_ARRAY) {
	this->list = new ArrayList<AbstractExtObject>();
}

ExtDomArrayObject::~ExtDomArrayObject() {
	this->list->deleteElements();
	delete this->list;
}

void ExtDomArrayObject::add(AbstractExtObject* obj) noexcept {
	this->list->addElement(obj);
}

} /* namespace alinous */
