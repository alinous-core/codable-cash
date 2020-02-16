/*
 * VmArrayInstanceUtils.h
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#ifndef INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_
#define INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_

#include "instance_array/VmArrayInstance.h"

namespace alinous {

class AnalyzedType;
class VmArrayInstance;
class VirtualMachine;

class VmArrayInstanceUtils {
public:
	static bool isArrayIndex(AnalyzedType& type) noexcept;
	static VmArrayInstance* buildArrayInstance(VirtualMachine* vm, int* dims, int size);
};

} /* namespace alinous */

#endif /* INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_ */
