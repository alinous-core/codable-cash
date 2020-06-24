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
#include "instance_parts/VMemHashMapKeySet.h"

#include "instance_string/VmStringInstance.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"
#include "base/Iterator.h"

#include "instance_ref/PrimitiveReference.h"


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

TEST(TestVmHashGroup, put03){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	UnicodeString strkey(L"key");
	UnicodeString strkey2(L"key");
	UnicodeString str(L"Hello World");
	UnicodeString str2(L"Hello World 2");

	VmStringInstance* key = new(vm) VmStringInstance(vm, &strkey); __STP(key);
	VmStringInstance* key2 = new(vm) VmStringInstance(vm, &strkey2); __STP(key2);
	VmStringInstance* value = new(vm) VmStringInstance(vm, &str); __STP(value);
	VmStringInstance* value2 = new(vm) VmStringInstance(vm, &str2); __STP(value2);

	VMemHashmap<VmStringInstance, VmStringInstance>* map = new(vm) VMemHashmap<VmStringInstance, VmStringInstance>(vm);

	VmStringInstance* last = map->put(key, value);
	CHECK(last == nullptr);

	last = map->put(key2, value2);
	CHECK(last != nullptr);

	VmStringInstance* str2eq = map->get(key2);
	CHECK(str2eq->valueCompare(value2) == 0)

	delete map;
}

TEST(TestVmHashGroup, keySet){
	VirtualMachine* vm = new VirtualMachine(1024 * 1024); __STP(vm);

	VMemHashmap<VmStringInstance, VmStringInstance>* map = new(vm) VMemHashmap<VmStringInstance, VmStringInstance>(vm);

	for(int i = 0; i != 1000; ++i){
		UnicodeString keystr(L"key");
		keystr.append(i);

		UnicodeString valuestr(L"value");
		valuestr.append(i);

		VmStringInstance* key = new(vm) VmStringInstance(vm, &keystr); __STP(key);
		VmStringInstance* value = new(vm) VmStringInstance(vm, &valuestr);

		map->put(key, value);
	}

	VMemHashMapKeySet<VmStringInstance, VmStringInstance>* keyset = map->keySet();
	Iterator<VmStringInstance> *it = keyset->iterator();
	while(it->hasNext()){
		const VmStringInstance* key = it->next();
		VmStringInstance* value = map->get(key);

		delete value;
	}

	delete it;
	delete map;
}

TEST(TestVmHashGroup, keySet02){
	VirtualMachine* vm = new VirtualMachine(1024 * 1024); __STP(vm);

	VMemHashmap<PrimitiveReference, VmStringInstance>* map = new(vm) VMemHashmap<PrimitiveReference, VmStringInstance>(vm);

	for(int i = 0; i != 1000; ++i){
		PrimitiveReference* key = PrimitiveReference::createIntReference(vm, i);

		UnicodeString valuestr(L"value");
		valuestr.append(i);

		VmStringInstance* value = new(vm) VmStringInstance(vm, &valuestr);

		map->put(key, value);
	}

	VMemHashMapKeySet<PrimitiveReference, VmStringInstance>* keyset = map->keySet();
	Iterator<PrimitiveReference> *it = keyset->iterator();

	while(it->hasNext()){
		const PrimitiveReference* key = it->next();
		VmStringInstance* value = map->get(key);

		delete value;
	}

	delete it;
	delete map;
}

TEST(TestVmHashGroup, keySetWithNull){
	VirtualMachine* vm = new VirtualMachine(1024 * 1024); __STP(vm);

	VMemHashmap<PrimitiveReference, VmStringInstance>* map = new(vm) VMemHashmap<PrimitiveReference, VmStringInstance>(vm);

	for(int i = 0; i != 1000; ++i){
		PrimitiveReference* key = PrimitiveReference::createIntReference(vm, i);

		UnicodeString valuestr(L"value");
		valuestr.append(i);

		VmStringInstance* value = new(vm) VmStringInstance(vm, &valuestr);

		map->put(key, value);
	}

	UnicodeString valuestr(L"value");
	VmStringInstance* value = new(vm) VmStringInstance(vm, &valuestr);
	map->put(nullptr, value);

	VMemHashMapKeySet<PrimitiveReference, VmStringInstance>* keyset = map->keySet();
	Iterator<PrimitiveReference> *it = keyset->iterator();

	while(it->hasNext()){
		const PrimitiveReference* key = it->next();
		VmStringInstance* value = map->get(key);

		delete value;
	}

	map->clear();

	delete it;
	delete map;
}

TEST(TestVmHashGroup, keySetWithNull02){
	VirtualMachine* vm = new VirtualMachine(1024 * 1024); __STP(vm);

	VMemHashmap<PrimitiveReference, VmStringInstance>* map = new(vm) VMemHashmap<PrimitiveReference, VmStringInstance>(vm);

	UnicodeString valuestr(L"value");
	VmStringInstance* value = new(vm) VmStringInstance(vm, &valuestr);
	map->put(nullptr, value);

	VmStringInstance* last = map->put(nullptr, nullptr);
	delete last;

	map->clear();

	delete map;
}
