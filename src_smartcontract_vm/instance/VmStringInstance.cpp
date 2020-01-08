/*
 * VmStringInstance.cpp
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#include "instance/VmStringInstance.h"

#include "instance/VmInstanceTypesConst.h"


namespace alinous {

VmStringInstance::VmStringInstance() : AbstractVmInstance(VmInstanceTypesConst::INST_STRING) {
}

VmStringInstance::~VmStringInstance() {
}

} /* namespace alinous */
