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

#include "instance_gc/GcManager.h"


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

	arrayRef->substitute(nullptr, &vm);

	GcManager* gc = vm.getGc();
	gc->garbageCollect();
}

TEST(TestArrayCompareGroup, compare03){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	atype.setDim(1);

	int dims[1] = {3};

	VmArrayInstanceUtils::isArrayIndex(atype);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(&atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	AbstractReference* ref2 = RefereceFactory::createReferenceFromAnalyzedType(&atype, &vm); __STP(ref2);
	ArrayReference* arrayRef2 = dynamic_cast<ArrayReference*>(ref2);


	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	arrayRef->substitute(inst, &vm);

	int diff = arrayRef->valueCompare(arrayRef2);
	CHECK(diff != 0)

	arrayRef->substitute(nullptr, &vm);
	arrayRef2->substitute(nullptr, &vm);

	GcManager* gc = vm.getGc();
	gc->garbageCollect();
}

TEST(TestArrayCompareGroup, compare04){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	atype.setDim(1);

	int dims[1] = {3};

	VmArrayInstanceUtils::isArrayIndex(atype);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(&atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	AbstractReference* ref2 = RefereceFactory::createReferenceFromAnalyzedType(&atype, &vm); __STP(ref2);
	ArrayReference* arrayRef2 = dynamic_cast<ArrayReference*>(ref2);


	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);
	VmArrayInstance* inst2 = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	arrayRef->substitute(inst, &vm);
	arrayRef2->substitute(inst2, &vm);

	int diff = arrayRef->valueCompare(arrayRef2);
	CHECK(diff != 0)


	arrayRef->substitute(nullptr, &vm);
	arrayRef2->substitute(nullptr, &vm);

	GcManager* gc = vm.getGc();
	gc->garbageCollect();
}

TEST(TestArrayCompareGroup, compare05){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	atype.setDim(1);

	int dims[1] = {3};

	VmArrayInstanceUtils::isArrayIndex(atype);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(&atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	AbstractReference* ref2 = RefereceFactory::createReferenceFromAnalyzedType(&atype, &vm); __STP(ref2);
	ArrayReference* arrayRef2 = dynamic_cast<ArrayReference*>(ref2);


	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	arrayRef->substitute(inst, &vm);

	int diff = arrayRef->valueCompare(inst);
	CHECK(diff != 0)

	arrayRef->substitute(nullptr, &vm);
	arrayRef2->substitute(nullptr, &vm);

	GcManager* gc = vm.getGc();
	gc->garbageCollect();
}

