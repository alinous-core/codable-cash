/*
 * ExtClassObject.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "base/UnicodeString.h"

#include "instance/VmInstanceTypesConst.h"


namespace alinous {

ExtClassObject::ExtClassObject(const UnicodeString* name) : AbstractExtObject(name, VmInstanceTypesConst::ISNT_OBJ) {
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
	this->map->put(obj->getName(), obj);
}

ExtPrimitiveObject* ExtClassObject::getExtPrimitiveObject(const UnicodeString* name) const noexcept {
	AbstractExtObject* obj = this->map->get(name);
	return dynamic_cast<ExtPrimitiveObject*>(obj);
}

ExtClassObject* ExtClassObject::getExtClassObject(const UnicodeString* name) const noexcept {
	AbstractExtObject* obj = this->map->get(name);
	return dynamic_cast<ExtClassObject*>(obj);
}

} /* namespace alinous */
