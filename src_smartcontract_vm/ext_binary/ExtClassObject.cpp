/*
 * ExtClassObject.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"
#include "ext_binary/ExtArrayObject.h"
#include "ext_binary/ExtStringClass.h"
#include "ext_binary/ExtExceptionObject.h"

#include "base/UnicodeString.h"

#include "instance/VmInstanceTypesConst.h"


namespace alinous {

ExtClassObject::ExtClassObject(const UnicodeString* name) : AbstractExtObject(name, VmInstanceTypesConst::INST_OBJ) {
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

	if(obj == nullptr || obj->isNull()){
		return nullptr;
	}

	return dynamic_cast<ExtClassObject*>(obj);
}

ExtExceptionObject* ExtClassObject::getExtExceptionObject(const UnicodeString* name) const noexcept {
	AbstractExtObject* obj = this->map->get(name);

	if(obj == nullptr || obj->isNull()){
		return nullptr;
	}

	return dynamic_cast<ExtExceptionObject*>(obj);
}

ExtArrayObject* ExtClassObject::getExtArrayObject(const UnicodeString* name) const noexcept {
	AbstractExtObject* obj = this->map->get(name);
	return dynamic_cast<ExtArrayObject*>(obj);
}

ExtStringClass* alinous::ExtClassObject::getExtStringObject(const UnicodeString* name) const noexcept {
	AbstractExtObject* obj = this->map->get(name);

	if(obj->isNull()){
		return nullptr;
	}

	return dynamic_cast<ExtStringClass*>(obj);
}

} /* namespace alinous */
