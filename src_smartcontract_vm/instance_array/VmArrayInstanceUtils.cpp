/*
 * VmArrayInstanceUtils.cpp
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#include "instance_array/VmArrayInstanceUtils.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_array/VmArrayInstance.h"

#include "vm/VirtualMachine.h"


namespace alinous {

bool VmArrayInstanceUtils::isArrayIndex(AnalyzedType& type) noexcept {
	return !type.isArray() &&
			(
					type.getType() == AnalyzedType::TYPE_BYTE ||
					type.getType() == AnalyzedType::TYPE_CHAR ||
					type.getType() == AnalyzedType::TYPE_SHORT ||
					type.getType() == AnalyzedType::TYPE_INT ||
					type.getType() == AnalyzedType::TYPE_LONG
			);
}


VmArrayInstance* VmArrayInstanceUtils::buildArrayInstance(VirtualMachine* vm, int* dims, int size) {
	VmArrayInstance* inst = new(vm) VmArrayInstance(vm);

	return inst;
}



} /* namespace alinous */
