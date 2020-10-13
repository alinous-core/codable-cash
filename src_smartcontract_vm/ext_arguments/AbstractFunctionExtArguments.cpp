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

#include "instance/instance_ref/AbstractReference.h"
#include "instance/instance_ref/ObjectReference.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_string/VmStringInstance.h"

namespace alinous {

AbstractFunctionExtArguments::AbstractFunctionExtArguments() {
}

AbstractFunctionExtArguments::~AbstractFunctionExtArguments() {
}

} /* namespace alinous */
