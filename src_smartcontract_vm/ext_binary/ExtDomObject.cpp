/*
 * ExtDomObject.cpp
 *
 *  Created on: 2020/06/25
 *      Author: iizuka
 */

#include "ext_binary/ExtDomObject.h"

#include "instance/VmInstanceTypesConst.h"

namespace alinous {

ExtDomObject::ExtDomObject(const UnicodeString* name) : AbstractExtObject(name, VmInstanceTypesConst::INST_DOM) {

}

ExtDomObject::~ExtDomObject() {

}

} /* namespace alinous */
