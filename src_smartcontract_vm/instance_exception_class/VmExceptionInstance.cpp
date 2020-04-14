/*
 * VmExceptionInstance.cpp
 *
 *  Created on: 2020/04/14
 *      Author: iizuka
 */

#include "instance_exception_class/VmExceptionInstance.h"

namespace alinous {

VmExceptionInstance::VmExceptionInstance(AnalyzedClass* clazz, VirtualMachine* vm)
				: VmClassInstance(clazz, vm) {

}

VmExceptionInstance::~VmExceptionInstance() {

}

} /* namespace alinous */
