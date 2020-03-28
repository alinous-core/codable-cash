/*
 * ExtNullPtrObject.cpp
 *
 *  Created on: 2020/03/28
 *      Author: iizuka
 */

#include "ext_binary/ExtNullPtrObject.h"

namespace alinous {

ExtNullPtrObject::ExtNullPtrObject(const UnicodeString* name, uint8_t type) : AbstractExtObject(name, type){
}

ExtNullPtrObject::~ExtNullPtrObject() {
}

} /* namespace alinous */
