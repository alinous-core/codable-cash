/*
 * ExtClassObject.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#include "ext_binary/ExtClassObject.h"

#include "base/UnicodeString.h"

#include "instance/VmInstanceTypesConst.h"

namespace alinous {

ExtClassObject::ExtClassObject(UnicodeString* name) : AbstractExtObject(name, VmInstanceTypesConst::ISNT_OBJ) {
	this->list = new ArrayList<AbstractExtObject>();
	this->map = new HashMap<UnicodeString, AbstractExtObject>();
}

ExtClassObject::~ExtClassObject() {
	this->list->deleteElements();

	delete this->list;
	delete this->map;
}

void ExtClassObject::add(AbstractExtObject* obj) noexcept {
	this->list->addElement(obj);
}

} /* namespace alinous */
