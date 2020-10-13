/*
 * VmArrayInstanceUtils.h
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#ifndef INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_
#define INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_

#include "instance/instance_array/VmArrayInstance.h"

namespace alinous {

class AnalyzedType;
class VmArrayInstance;
class VirtualMachine;
class IAbstractVmInstanceSubstance;

class VmArrayInstanceUtils {
public:
	static bool isArrayIndex(AnalyzedType& type) noexcept;
	static VmArrayInstance* buildArrayInstance(VirtualMachine* vm, int* dims, int size, const AnalyzedType* atype);

private:
	static void makeDimension(VirtualMachine* vm, int maxDepth, int current, ArrayList<AbstractReference>* lastRefs, int length, const AnalyzedType* atype);
	static void setupVmArrayInstance(VirtualMachine* vm, VmArrayInstance* inst, int length, const AnalyzedType* atype
										, ArrayList<AbstractReference>* refs, int maxDepth, int current);

	static AbstractReference* makeReference(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm, int depth, int current, const AnalyzedType* atype);
};

} /* namespace alinous */

#endif /* INSTANCE_ARRAY_VMARRAYINSTANCEUTILS_H_ */
