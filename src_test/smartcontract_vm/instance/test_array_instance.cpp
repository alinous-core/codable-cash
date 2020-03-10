/*
 * test_array_instance.cpp
 *
 *  Created on: 2020/03/09
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "../VmTestUtils.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref/ObjectReference.h"
#include "instance_ref/RefereceFactory.h"

#include "instance_array/ArrayReference.h"
#include "instance_array/VmArrayInstanceUtils.h"

#include "instance_gc/GcManager.h"

#include "instance_ref/PrimitiveReference.h"

using namespace alinous;

TEST_GROUP(TestArrayInstanceGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestArrayInstanceGroup, testSet){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	int32_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, val);
	inst->setReference(&vm, 1, ref);

	const VMemList<AbstractReference>* list = inst->getReferences();

	GcManager* gc = vm.getGc();
	inst->removeInnerRefs(gc);
	delete inst;

	gc->garbageCollect();

}
