/*
 * test_dom_base.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

#include "instance_dom/DomVariableInstance.h"

#include "instance_ref/VmRootReference.h"
#include "instance_ref/AbstractReference.h"

#include "instance_gc/GcManager.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_string/VmStringInstance.h"

#include "instance_dom/DomRuntimeReference.h"
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

		const VMemList<AbstractReference>* list = dom->getInstReferences();

		gc->removeObject(ref);

		gc->garbageCollect();
	}
}
