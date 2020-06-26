/*
 * ExtDomObject.cpp
 *
 *  Created on: 2020/06/25
 *      Author: iizuka
 */

#include "ext_binary/ExtDomObject.h"
#include "ext_binary/AbstractExtObject.h"

#include "instance/VmInstanceTypesConst.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

namespace alinous {

ExtDomObject::ExtDomObject(const UnicodeString* name) : AbstractExtObject(name, VmInstanceTypesConst::INST_DOM) {
	this->properties = new HashMap<UnicodeString, AbstractExtObject>();
}

ExtDomObject::~ExtDomObject() {
	Iterator<UnicodeString>* it = this->properties->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		AbstractExtObject* exobj  = this->properties->get(key);

		delete exobj;
	}

	delete this->properties;
}

void ExtDomObject::put(const UnicodeString* name, AbstractExtObject* value) noexcept {
	this->properties->put(name, value);
}

AbstractExtObject* ExtDomObject::get(const UnicodeString* name) const noexcept {
	return this->properties->get(name);
}

} /* namespace alinous */
