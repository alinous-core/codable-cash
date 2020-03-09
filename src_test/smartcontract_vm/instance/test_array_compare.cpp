/*
 * test_array_compare.cpp
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

#include "instance/VmClassInstance.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref/ObjectReference.h"
#include "instance_ref/RefereceFactory.h"

#include "instance_array/ArrayReference.h"

#include "instance_array/VmArrayInstanceUtils.h"
using namespace alinous;

TEST_GROUP(TestArrayCompareGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestArrayCompareGroup, compare01){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	VmArrayInstanceUtils::isArrayIndex(atype);

	atype.setDim(1);

	VmArrayInstanceUtils::isArrayIndex(atype);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(&atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	int diff = arrayRef->valueCompare(arrayRef);
	CHECK(diff == 0)
}

TEST(TestArrayCompareGroup, compare02){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	atype.setDim(1);

	int dims[1] = {3};

	VmArrayInstanceUtils::isArrayIndex(atype);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(&atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	arrayRef->substitute(inst, &vm);
	arrayRef->substitute(inst, &vm);

	int diff = arrayRef->valueCompare(arrayRef);
	CHECK(diff == 0)
}
