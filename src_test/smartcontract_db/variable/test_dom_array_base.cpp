/*
 * test_dom_array_base.cpp
 *
 *  Created on: 2020/07/11
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

#include "instance_dom/DomVariableInstance.h"

#include "instance_ref/VmRootReference.h"
#include "instance_ref/AbstractReference.h"
#include "instance_ref/PrimitiveReference.h"

#include "instance_gc/GcManager.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_string/VmStringInstance.h"

#include "instance_dom/DomRuntimeReference.h"
#include "instance_dom/DomArrayVariable.h"

#include "ext_binary/AbstractExtObject.h"

using namespace alinous;

TEST_GROUP(TestDomArrayBaseGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestDomArrayBaseGroup, case01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		DomArrayVariable* val = new(vm) DomArrayVariable(vm); __STP(val);
		AnalyzedType at = val->getRuntimeType();

		CHECK(at.getType() == AnalyzedType::TYPE_DOM_ARRAY);
	}
}

TEST(TestDomArrayBaseGroup, case02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);

		DomArrayVariable* val = new(vm) DomArrayVariable(vm);
		AbstractReference* ref = val->wrap(root, vm);

		gc->registerObject(ref);

		PrimitiveReference* pr = PrimitiveReference::createIntReference(vm ,1);
		val->add(vm, pr);

		const VMemList<AbstractReference>* list = val->getInstReferences();
		CHECK(list->size() == 1);

		gc->removeObject(ref);

		gc->garbageCollect();
	}
}

TEST(TestDomArrayBaseGroup, case03){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);

		DomArrayVariable* val = new(vm) DomArrayVariable(vm);
		AbstractReference* ref = val->wrap(root, vm);

		gc->registerObject(ref);

		PrimitiveReference* pr = PrimitiveReference::createIntReference(vm ,1);
		val->add(vm, pr);
		PrimitiveReference* pr2 = PrimitiveReference::createIntReference(vm ,2);
		val->add(vm, pr2);

		val->add(vm, nullptr);

		const UnicodeString* str = ref->toString();
		UnicodeString ans(L"[1, 2, null]");
		CHECK(ans.equals(str));

		gc->removeObject(ref);

		gc->garbageCollect();
	}
}

TEST(TestDomArrayBaseGroup, case04){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);

		DomArrayVariable* val = new(vm) DomArrayVariable(vm);
		AbstractReference* ref = val->wrap(root, vm);

		gc->registerObject(ref);

		PrimitiveReference* pr = PrimitiveReference::createIntReference(vm ,1);
		val->add(vm, pr);
		PrimitiveReference* pr2 = PrimitiveReference::createIntReference(vm ,2);
		val->add(vm, pr2);
		val->add(vm, nullptr);


		UnicodeString str(L"name");
		VTableRegistory* table = nullptr;
		AbstractExtObject* ext = val->instToClassExtObject(&str, table); __STP(ext);

		CHECK(ext != nullptr)

		gc->removeObject(ref);
		gc->garbageCollect();
	}
}

TEST(TestDomArrayBaseGroup, case05){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);

		DomArrayVariable* val = new(vm) DomArrayVariable(vm);
		AbstractReference* ref = val->wrap(root, vm);
		gc->registerObject(ref);

		DomArrayVariable* val2 = new(vm) DomArrayVariable(vm);
		AbstractReference* ref2 = val2->wrap(root, vm);
		gc->registerObject(ref2);


		CHECK(val->instValueCompare(val) == 0)
		CHECK(val->instValueCompare(val2) != 0)

		CHECK(ref->valueCompare(ref->getInstance()) == 0);
		CHECK(ref->valueCompare(ref2->getInstance()) != 0);

		gc->removeObject(ref);
		gc->removeObject(ref2);
		gc->garbageCollect();
	}
}
