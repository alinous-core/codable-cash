/*
 * VmClassInstance.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "instance/VmClassInstance.h"
#include "instance_ref/AbstractReference.h"

#include "vm/VirtualMachine.h"

namespace alinous {

VmClassInstance::VmClassInstance(AnalyzedClass* clazz, VirtualMachine* vm) :
		AbstractVmInstance(AbstractVmInstance::ISNT_OBJ), clazz(clazz), members(vm) {

}

VmClassInstance::~VmClassInstance() {
}

} /* namespace alinous */
