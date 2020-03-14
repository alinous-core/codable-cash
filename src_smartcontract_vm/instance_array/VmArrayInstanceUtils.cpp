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

#include "instance/VmInstanceTypesConst.h"
namespace alinous {

bool VmArrayInstanceUtils::isArrayIndex(AnalyzedType& type) noexcept {
	uint8_t t = type.getType();

	return !type.isArray() &&
			(
					t == AnalyzedType::TYPE_BYTE ||
					t == AnalyzedType::TYPE_CHAR ||
					t == AnalyzedType::TYPE_SHORT ||
					t == AnalyzedType::TYPE_INT ||
					t == AnalyzedType::TYPE_LONG
			);
}


VmArrayInstance* VmArrayInstanceUtils::buildArrayInstance(VirtualMachine* vm, int* dims, int size, const AnalyzedType* atype) {
	int length = dims[0];

	ArrayList<AbstractReference> lastRefs;

	VmArrayInstance* inst = new(vm) VmArrayInstance(vm, length);
	for(int i = 0; i != length; ++i){
		AbstractReference* ref = makeReference(vm, size, 0, atype);
		inst->setReference(vm, i, ref);
		lastRefs.addElement(ref);
	}


	for(int i = 1; i != size; ++i){
		length = dims[i];
		makeDimension(vm, size, i, &lastRefs, length, atype);
	}

	return inst;
}

void VmArrayInstanceUtils::makeDimension(VirtualMachine* vm, int maxDepth, int current, ArrayList<AbstractReference>* lastRefs, int length, const AnalyzedType* atype) {
	ArrayList<AbstractReference> refs;

	int maxLoop = lastRefs->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = lastRefs->get(i);

		ArrayReference* arrayReference = dynamic_cast<ArrayReference*>(ref);

		VmArrayInstance* inst = new(vm) VmArrayInstance(vm, length);
		ref->substitute(inst, vm);

		setupVmArrayInstance(vm, inst, length, atype, &refs, maxDepth, current);
	}

	lastRefs->reset();
	lastRefs->addAll(&refs);
}

void VmArrayInstanceUtils::setupVmArrayInstance(VirtualMachine* vm, VmArrayInstance* inst,
		int length, const AnalyzedType* atype, ArrayList<AbstractReference>* refs, int maxDepth, int current) {
	for(int i = 0; i != length; ++i){
		AbstractReference* ref = makeReference(vm, maxDepth, current, atype);
		inst->setReference(vm, i, ref);
		refs->addElement(ref);
	}

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
