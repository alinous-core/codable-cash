/*
 * test_vm_hash.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

#include "instance_dom/DomVariableInstance.h"

#include "instance_parts/VMemHashmap.h"

#include "instance_string/VmStringInstance.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"


using namespace alinous;

TEST_GROUP(TestVmHashGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestVmHashGroup, case01){
	VirtualMachine vm(1024 * 10);

	VMemHashmap<UnicodeString, UnicodeString>* map = new(&vm) VMemHashmap<UnicodeString, UnicodeString>(&vm);
	delete map;
}

TEST(TestVmHashGroup, put01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	UnicodeString strkey(L"key");
	UnicodeString str(L"Hello World");

	VmStringInstance* key = new(vm) VmStringInstance(vm, &strkey); __STP(key);
	VmStringInstance* value = new(vm) VmStringInstance(vm, &str); __STP(value);

	VMemHashmap<VmStringInstance, VmStringInstance>* map = new(vm) VMemHashmap<VmStringInstance, VmStringInstance>(vm);

	VmStringInstance* last = map->put(key, value);
	CHECK(last == nullptr);

	delete map;
}

TEST(TestVmHashGroup, put02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	UnicodeString strkey(L"key");
	UnicodeString str(L"Hello World");
	UnicodeString str2(L"Hello World 2");

	VmStringInstance* key = new(vm) VmStringInstance(vm, &strkey); __STP(key);
	VmStringInstance* value = new(vm) VmStringInstance(vm, &str); __STP(value);
	VmStringInstance* value2 = new(vm) VmStringInstance(vm, &str2); __STP(value2);

	VMemHashmap<VmStringInstance, VmStringInstance>* map = new(vm) VMemHashmap<VmStringInstance, VmStringInstance>(vm);

	VmStringInstance* last = map->put(key, value);
	CHECK(last == nullptr);

	last = map->put(key, value2);
	CHECK(last != nullptr);

	delete map;
}
