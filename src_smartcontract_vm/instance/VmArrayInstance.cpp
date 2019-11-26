/*
 * ArrayInstance.cpp
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#include "instance/VmArrayInstance.h"

namespace alinous {

VmArrayInstance::VmArrayInstance() : AbstractVmInstance(AbstractVmInstance::INST_ARRAY) {
}

VmArrayInstance::~VmArrayInstance() {

}

const VMemList<AbstractReference>* VmArrayInstance::getReferences() const noexcept {
	// FIXME getReferences()
	return nullptr;
}

} /* namespace alinous */
