/*
 * ArrayInstance.cpp
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#include "instance/VmArrayInstance.h"

#include "instance/VmInstanceTypesConst.h"

namespace alinous {

VmArrayInstance::VmArrayInstance() : AbstractVmInstance(VmInstanceTypesConst::INST_ARRAY) {
}

VmArrayInstance::~VmArrayInstance() {

}

const VMemList<AbstractReference>* VmArrayInstance::getReferences() const noexcept {
	// FIXME getReferences()
	return nullptr;
}

} /* namespace alinous */
