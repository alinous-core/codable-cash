/*
 * ExtExceptionObject.cpp
 *
 *  Created on: 2020/04/16
 *      Author: iizuka
 */

#include "ext_binary/ExtExceptionObject.h"

#include "instance/VmInstanceTypesConst.h"
namespace alinous {

ExtExceptionObject::ExtExceptionObject(const UnicodeString* name) : AbstractExtObject(name, VmInstanceTypesConst::INST_EXCEPTION) {

}

ExtExceptionObject::~ExtExceptionObject() {

}

} /* namespace alinous */
