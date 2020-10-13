/*
 * test_dom_base.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_dom/DomVariableInstance.h"

#include "instance/instance_ref/VmRootReference.h"
#include "instance/instance_ref/AbstractReference.h"

#include "instance/instance_gc/GcManager.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_string/VmStringInstance.h"

#include "instance/instance_dom/DomRuntimeReference.h"

#include "ext_binary/AbstractExtObject.h"

using namespace alinous;

TEST_GROUP(TestDomBaseGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestDomBaseGroup, case01){
	VirtualMachine vm(1024 * 10);

	DomVariableInstance* dom = new(&vm) DomVariableInstance(&vm);

	delete dom;
}

TEST(TestDomBaseGroup, case02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);

		DomVariableInstance* dom = new(vm) DomVariableInstance(vm);
		AbstractReference* ref = dom->wrap(root, vm); __STP(ref);
		gc->registerObject(ref);

		gc->removeObject(ref);

		gc->garbageCollect();
	}
}

TEST(TestDomBaseGroup, case03){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);

		DomVariableInstance* dom = new(vm) DomVariableInstance(vm);
		AbstractReference* ref = dom->wrap(root, vm); __STP(ref);
		gc->registerObject(ref);

		AnalyzedType at = dom->getRuntimeType();
		CHECK(at.getType() == AnalyzedType::TYPE_DOM)

		gc->removeObject(ref);

		gc->garbageCollect();
	}
}

TEST(TestDomBaseGroup, case04){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);
		UnicodeString prop(L"prop");

		DomVariableInstance* dom = new(vm) DomVariableInstance(vm);
		VmStringInstance* vmstr = new(vm) VmStringInstance(vm, &prop); __STP(vmstr);

		dom->putProperty(vm, vmstr, nullptr);

		AbstractReference* ref = dom->wrap(root, vm); __STP(ref);
		gc->registerObject(ref);

		const VMemList<AbstractReference>* list = dom->getInstReferences();

		gc->removeObject(ref);

		gc->garbageCollect();
	}
}

TEST(TestDomBaseGroup, case05){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);
		UnicodeString prop(L"prop");

		DomVariableInstance* dom = new(vm) DomVariableInstance(vm);
		VmStringInstance* vmstr = new(vm) VmStringInstance(vm, &prop); __STP(vmstr);

		dom->putProperty(vm, vmstr, nullptr);
		dom->putProperty(vm, vmstr, nullptr);

		AbstractReference* ref = dom->wrap(root, vm); __STP(ref);
		gc->registerObject(ref);

		const VMemList<AbstractReference>* list = dom->getInstReferences();

		gc->removeObject(ref);

		gc->garbageCollect();

		CHECK(gc->isEmpty());
	}
}

TEST(TestDomBaseGroup, case06){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);
		UnicodeString prop(L"prop");
		UnicodeString prop2(L"prop2");
		UnicodeString value(L"value");
		UnicodeString value2(L"value2");

		DomVariableInstance* dom = new(vm) DomVariableInstance(vm);
		VmStringInstance* vmstr = new(vm) VmStringInstance(vm, &prop); __STP(vmstr);
		VmStringInstance* vmstr2 = new(vm) VmStringInstance(vm, &prop2); __STP(vmstr2);

		VmStringInstance* vmvalue = new(vm) VmStringInstance(vm, &value);
		VmStringInstance* vmvalue2 = new(vm) VmStringInstance(vm, &value2);

		dom->putProperty(vm, vmstr, vmvalue);
		dom->putProperty(vm, vmstr2, vmvalue2);

		AbstractReference* ref = dom->wrap(root, vm); __STP(ref);
		gc->registerObject(ref);

		const UnicodeString* tostr = ref->toString();

		UnicodeString pattern(L"{prop2 : \"value2\", prop : \"value\"}");
		UnicodeString pattern2(L"{prop : \"value\", prop2 : \"value2\"}");

		CHECK(tostr->equals(pattern) || tostr->equals(pattern2));

		gc->removeObject(ref);
		gc->garbageCollect();

		CHECK(gc->isEmpty());
	}
}

TEST(TestDomBaseGroup, case07){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);
		DomVariableInstance* dom = new(vm) DomVariableInstance(vm);

		AbstractReference* ref = dom->wrap(root, vm); __STP(ref);
		gc->registerObject(ref);

		int result = dom->instValueCompare(nullptr);
		CHECK(result != -1)

		result = dom->instValueCompare(dom);
		CHECK(result == 0)

		gc->removeObject(ref);
		gc->garbageCollect();

		CHECK(gc->isEmpty());
	}
}

TEST(TestDomBaseGroup, case08){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);
		DomVariableInstance* dom = new(vm) DomVariableInstance(vm);

		AbstractReference* ref = dom->wrap(root, vm); __STP(ref);
		gc->registerObject(ref);

		UnicodeString str(L"name");
		VTableRegistory* table = nullptr;
		AbstractExtObject* ext = dom->instToClassExtObject(&str, table); __STP(ext);

		gc->removeObject(ref);
		gc->garbageCollect();

		CHECK(gc->isEmpty());
	}
}

TEST(TestDomBaseGroup, case09){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		VmRootReference* root = new(vm) VmRootReference(vm); __STP(root);

		DomRuntimeReference* refref = new(vm) DomRuntimeReference(root, vm); __STP(refref);
		gc->registerObject(refref);

		DomVariableInstance* dom = new(vm) DomVariableInstance(vm);

		int result = refref->valueCompare(nullptr);
		CHECK(result == 0)

		result = refref->valueCompare(dom);
		CHECK(result != 0)

		refref->substitute(dom, vm);

		result = refref->valueCompare(nullptr);
		CHECK(result != 0)

		result = refref->valueCompare(dom);
		CHECK(result == 0)

		gc->removeObject(refref);
		gc->garbageCollect();

		CHECK(gc->isEmpty());
	}
}


