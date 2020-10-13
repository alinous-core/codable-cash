/*
 * test_array_compare.cpp
 *
 *  Created on: 2020/03/09
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "../VmTestUtils.h"

#include "instance/VmClassInstance.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/ObjectReference.h"
#include "instance/instance_ref/RefereceFactory.h"

#include "instance/instance_array/ArrayReference.h"

#include "instance/instance_array/VmArrayInstanceUtils.h"

#include "instance/instance_gc/GcManager.h"

#include "instance/instance_ref/VmRootReference.h"

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

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(nullptr, &atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	int diff = arrayRef->valueCompare(arrayRef->getInstance());
	CHECK(diff == 0)
}

TEST(TestArrayCompareGroup, compare02){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	atype.setDim(1);

	int dims[1] = {3};

	VmArrayInstanceUtils::isArrayIndex(atype);

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(root, &atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	GcManager* gc = vm.getGc();
	arrayRef->substitute(inst, &vm);
	arrayRef->substitute(inst, &vm);

	int diff = arrayRef->valueCompare(arrayRef->getInstance());
	CHECK(diff == 0)

	arrayRef->substitute(nullptr, &vm);

	gc->garbageCollect();

	delete root;
}

TEST(TestArrayCompareGroup, compare03){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	atype.setDim(1);

	int dims[1] = {3};

	VmArrayInstanceUtils::isArrayIndex(atype);

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(root, &atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	AbstractReference* ref2 = RefereceFactory::createReferenceFromAnalyzedType(root, &atype, &vm); __STP(ref2);
	ArrayReference* arrayRef2 = dynamic_cast<ArrayReference*>(ref2);


	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	GcManager* gc = vm.getGc();
	arrayRef->substitute(inst, &vm);

	int diff = arrayRef->valueCompare(arrayRef2->getInstance());
	CHECK(diff != 0)

	arrayRef->substitute(nullptr, &vm);
	arrayRef2->substitute(nullptr, &vm);

	gc->garbageCollect();

	delete root;
}

TEST(TestArrayCompareGroup, compare04){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	atype.setDim(1);

	int dims[1] = {3};

	VmArrayInstanceUtils::isArrayIndex(atype);

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(root, &atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	AbstractReference* ref2 = RefereceFactory::createReferenceFromAnalyzedType(root, &atype, &vm); __STP(ref2);
	ArrayReference* arrayRef2 = dynamic_cast<ArrayReference*>(ref2);


	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);
	VmArrayInstance* inst2 = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	GcManager* gc = vm.getGc();
	arrayRef->substitute(inst, &vm);
	arrayRef2->substitute(inst2, &vm);

	int diff = arrayRef->valueCompare(arrayRef2->getInstance());
	CHECK(diff != 0)


	arrayRef->substitute(nullptr, &vm);
	arrayRef2->substitute(nullptr, &vm);

	gc->garbageCollect();

	delete root;
}

TEST(TestArrayCompareGroup, compare05){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_LONG);
	atype.setDim(1);

	int dims[1] = {3};

	VmArrayInstanceUtils::isArrayIndex(atype);

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(root, &atype, &vm); __STP(ref);
	ArrayReference* arrayRef = dynamic_cast<ArrayReference*>(ref);

	AbstractReference* ref2 = RefereceFactory::createReferenceFromAnalyzedType(root, &atype, &vm); __STP(ref2);
	ArrayReference* arrayRef2 = dynamic_cast<ArrayReference*>(ref2);


	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	GcManager* gc = vm.getGc();
	arrayRef->substitute(inst, &vm);

	int diff = arrayRef2->valueCompare(inst);
	CHECK(diff != 0)

	arrayRef->substitute(nullptr, &vm);
	arrayRef2->substitute(nullptr, &vm);

	gc->garbageCollect();

	delete root;
}

