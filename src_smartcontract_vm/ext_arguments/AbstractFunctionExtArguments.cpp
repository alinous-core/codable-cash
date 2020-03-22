/*
 * AbstractFunctionExtArguments.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "ext_arguments/AbstractFunctionExtArguments.h"
#include <cstdint>

#include "instance/AbstractVmInstance.h"
#include "instance/VmInstanceTypesConst.h"

#include "instance_ref/AbstractReference.h"
#include "instance_ref/ObjectReference.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_string/VmStringInstance.h"

namespace alinous {

AbstractFunctionExtArguments::AbstractFunctionExtArguments() {
}

AbstractFunctionExtArguments::~AbstractFunctionExtArguments() {
}

AbstractReference* AbstractFunctionExtArguments::toReference(VirtualMachine* vm, AbstractVmInstance* inst) {
	if(inst == nullptr){
		ObjectReference* ref = ObjectReference::createStringReference(nullptr, vm);
		return ref;
	}

	if(inst->isReference()){
		return dynamic_cast<AbstractReference*>(inst);
	}

	uint8_t type = inst->getType();
	assert(type == VmInstanceTypesConst::INST_STRING);

	VmStringInstance* strInst = dynamic_cast<VmStringInstance*>(inst);
	return ObjectReference::createStringReference(strInst, vm);
}

} /* namespace alinous */
