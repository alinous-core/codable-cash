/*
 * VmClassInstance.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "instance/VmClassInstance.h"

namespace alinous {

VmClassInstance::VmClassInstance(AnalyzedClass* clazz) : AbstractVmInstance(AbstractVmInstance::ISNT_OBJ), clazz(clazz) {

}

VmClassInstance::~VmClassInstance() {
}

} /* namespace alinous */
