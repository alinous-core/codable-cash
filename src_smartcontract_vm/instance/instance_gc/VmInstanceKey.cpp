/*
 * VmInstanceKey.cpp
 *
 *  Created on: 2019/07/06
 *      Author: iizuka
 */

#include "instance/instance_gc/VmInstanceKey.h"

#include "instance/AbstractVmInstance.h"
#include "instance/IAbstractVmInstanceSubstance.h"

namespace alinous {


VmInstanceKey::VmInstanceKey(const VmInstanceKey& inst) {
	this->instance = inst.instance;
}

VmInstanceKey::VmInstanceKey(const IAbstractVmInstanceSubstance* instance) {
	this->instance = instance;
}

VmInstanceKey::~VmInstanceKey() {
}

int VmInstanceKey::ValueCompare::operator ()(const VmInstanceKey* const _this, const VmInstanceKey* const object) const noexcept {
	return _this->instance - object->instance;
}

int VmInstanceKey::hashCode() const noexcept {
	return this->instance->instHashCode();
}

} /* namespace alinous */
