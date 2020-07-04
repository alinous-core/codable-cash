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
#include "instance_ref/VmRootReference.h"

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

TEST(TestArrayInstanceGroup, testInst){
	VirtualMachine vm(1024 * 10);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	int32_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, val);
	inst->setReference(&vm, 1, ref);

	CHECK(inst->getInstReferences() == inst->getReferences());

	const VMemList<AbstractReference>* list = inst->getReferences();

	GcManager* gc = vm.getGc();
	inst->removeInnerRefs(gc);
	delete inst;

	gc->garbageCollect();

}

TEST(TestArrayInstanceGroup, arrayCompareError){
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	AbstractReference* ref = new(&vm) ArrayReference(root, &vm);
	ref->substitute(inst, &vm);

	int32_t val = 1;
	PrimitiveReference* p = PrimitiveReference::createIntReference(&vm, val);

	int result = ref->valueCompare(p);
	CHECK(result < 0);

	GcManager* gc = vm.getGc();
	gc->removeObject(ref);
	gc->garbageCollect();

	delete ref;
	delete root;
	delete p;
}

TEST(TestArrayInstanceGroup, arrayCompareError2){
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	AbstractReference* ref = new(&vm) ArrayReference(root, &vm);
	ref->substitute(inst, &vm);


	int32_t val = 1;
	PrimitiveReference* p = PrimitiveReference::createIntReference(&vm, val);

	int result = inst->instValueCompare(p);
	CHECK(result != 0);

	GcManager* gc = vm.getGc();
	gc->removeObject(ref);
	gc->garbageCollect();

	delete ref;
	delete root;
	delete p;
}

TEST(TestArrayInstanceGroup, arrayinstToExtObj){
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);

	AbstractReference* ref = new(&vm) ArrayReference(root, &vm);
	ref->substitute(inst, &vm);


	int32_t val = 1;
	PrimitiveReference* p = PrimitiveReference::createIntReference(&vm, val);

	UnicodeString str(L"name");
	VTableRegistory* table = nullptr;
	AbstractExtObject* obj = ref->toClassExtObject(&str, table); __STP(obj);

	GcManager* gc = vm.getGc();
	gc->removeObject(ref);
	gc->garbageCollect();

	delete ref;
	delete root;
	delete p;
}

TEST(TestArrayInstanceGroup, arrayinstWrap){
	VirtualMachine vm(1024 * 10);
	GcManager* gc = vm.getGc();

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);
	AbstractReference* ref = inst->wrap(root, &vm);
	gc->registerObject(ref);

	AnalyzedType at = inst->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_INT);

	gc->removeObject(ref);
	gc->garbageCollect();

	delete ref;
	delete root;
}

TEST(TestArrayInstanceGroup, arrayinstWrapToStrong){
	VirtualMachine vm(1024 * 10);
	GcManager* gc = vm.getGc();

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);
	AbstractReference* ref = inst->wrap(root, &vm);
	gc->registerObject(ref);

	const UnicodeString* str = ref->toString();
	UnicodeString ans(L"0, 0, 0");

	CHECK(ans.equals(str))

	AnalyzedType at = inst->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_INT);

	gc->removeObject(ref);
	gc->garbageCollect();

	delete ref;
	delete root;
}

TEST(TestArrayInstanceGroup, arrayinstWrapToStrong02){
	VirtualMachine vm(1024 * 10);
	GcManager* gc = vm.getGc();

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);
	AbstractReference* ref = inst->wrap(root, &vm);
	gc->registerObject(ref);

	ref->substitute(nullptr, &vm);

	const UnicodeString* str = ref->toString();

	CHECK(AbstractReference::NULL_STR.equals(str))

	AnalyzedType at = inst->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_INT);

	gc->removeObject(ref);
	gc->garbageCollect();

	delete ref;
	delete root;
}

TEST(TestArrayInstanceGroup, arrayinstWrapToStrong03){
	VirtualMachine vm(1024 * 10);
	GcManager* gc = vm.getGc();

	VmRootReference* root = new(&vm) VmRootReference(&vm);

	AnalyzedType atype(AnalyzedType::TYPE_INT);
	atype.setDim(1);

	int dims[1] = {3};
	VmArrayInstance* inst = VmArrayInstanceUtils::buildArrayInstance(&vm, dims, 1, &atype);
	AbstractReference* ref = inst->wrap(root, &vm);
	gc->registerObject(ref);

	inst->setReference(&vm, 1, nullptr);

	const UnicodeString* str = ref->toString();
	UnicodeString ans(L"0, null, 0");

	CHECK(ans.equals(str))

	AnalyzedType at = inst->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_INT);

	gc->removeObject(ref);
	gc->garbageCollect();

	delete ref;
	delete root;
}
