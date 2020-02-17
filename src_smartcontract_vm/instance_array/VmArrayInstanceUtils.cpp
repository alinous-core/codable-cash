/*
 * VmArrayInstanceUtils.cpp
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#include "instance_array/VmArrayInstanceUtils.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_array/VmArrayInstance.h"
#include "instance_array/ArrayReference.h"

#include "vm/VirtualMachine.h"

#include "instance_ref/RefereceFactory.h"

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


VmArrayInstance* VmArrayInstanceUtils::buildArrayInstance(VirtualMachine* vm, int* dims, int size, const AnalyzedType* atype) {


	int length = dims[0];

	VmArrayInstance* inst = new(vm) VmArrayInstance(vm, length);
	for(int i = 0; i != length; ++i){
		AbstractReference* ref = makeReference(vm, size, 0, atype);
		inst->setReference(vm, i, ref);
	}



	return inst;
}

AbstractReference* VmArrayInstanceUtils::makeReference(VirtualMachine* vm, int depth, int current, const AnalyzedType* atype) {
	if(depth - 1 <= current){
		AnalyzedType baseType(*atype);
		baseType.setDim(0);

		AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(&baseType, vm);
		return ref;
	}

	return new(vm) ArrayReference(vm);
}

} /* namespace alinous */
