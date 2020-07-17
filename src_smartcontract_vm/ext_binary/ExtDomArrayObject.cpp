/*
 * ExtDomArrayObject.cpp
 *
 *  Created on: 2020/07/02
 *      Author: iizuka
 */

#include "ext_binary/ExtDomArrayObject.h"

#include "instance/VmInstanceTypesConst.h"

namespace alinous {

ExtDomArrayObject::ExtDomArrayObject(const UnicodeString* name) : AbstractExtObject(name, VmInstanceTypesConst::INST_DOM_ARRAY) {
	this->list = new ArrayList<AbstractExtObject>();
}

ExtDomArrayObject::~ExtDomArrayObject() {
	this->list->deleteElements();
	delete this->list;
}

void ExtDomArrayObject::add(AbstractExtObject* obj) noexcept {
	this->list->addElement(obj);
}

AbstractExtObject* ExtDomArrayObject::get(int pos) const noexcept {
	return this->list->get(pos);
}

int ExtDomArrayObject::size() const noexcept {
	return this->list->size();
}

AbstractExtObject* ExtDomArrayObject::copy() const noexcept {
	ExtDomArrayObject* newObj = new ExtDomArrayObject(getName());

	int maxLoop = this->list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExtObject* obj = this->list->get(i);

		newObj->add(obj == nullptr ? nullptr : obj->copy());
	}

	return newObj;
}

} /* namespace alinous */
