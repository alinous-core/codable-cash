/*
 * test_vm_mem_list_sort.cpp
 *
 *  Created on: 2020/06/25
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "instance/instance_parts/VmMalloc.h"
#include "instance/instance_parts/VMemList.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_parts/VMemPrimitiveList.h"

#include "base/Integer.h"

using namespace alinous;

TEST_GROUP(TestVmMemListSort) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

static void releaseInternalObjects(VMemList<Integer, Integer::ValueCompare>* ptr){
	int maxLoop = ptr->size();
	for(int i = 0; i != maxLoop; ++i){
		Integer* pInt = ptr->get(i);
		delete pInt;
	}
}

static void isSorted(VMemList<Integer, Integer::ValueCompare>* ptr){
	Integer* last = nullptr;

	int maxLoop = ptr->size();
	for(int i = 0; i != maxLoop; ++i){
		Integer* pInt = ptr->get(i);

		if(last){
			if(!(last->compareTo(pInt) <= 0)){
				throw -1;
			}
		}

		//printf("%d\n", pInt->value);


		last = pInt;
	}
}

TEST(TestVmMemListSort, sort01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	{
		VMemList<Integer, Integer::ValueCompare>* ar = new(vm) VMemList<Integer, Integer::ValueCompare>(vm, 8);
		__STP(ar);

		int maxLoop = 10;
		for(int i = 0; i != 10; ++i){
			Integer* pInt = new Integer(maxLoop - i);
			ar->addElement(pInt);
		}

		ar->sort();

		isSorted(ar);
		releaseInternalObjects(ar);
	}
}

TEST(TestVmMemListSort, sortInsert){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	{
		VMemList<Integer, Integer::ValueCompare>* ar = new(vm) VMemList<Integer, Integer::ValueCompare>(vm, 8);
		__STP(ar);

		int maxLoop = 10;
		for(int i = 0; i != 10; ++i){
			Integer* pInt = new Integer(maxLoop - i);
			ar->addElement(pInt);
		}

		ar->addElementWithSorted(new Integer(11));
		ar->addElementWithSorted(new Integer(0));
		ar->addElementWithSorted(new Integer(5));
		ar->addElementWithSorted(new Integer(-1));
		ar->addElementWithSorted(new Integer(-1));
		ar->addElementWithSorted(new Integer(100));
		ar->addElementWithSorted(new Integer(100));

		ar->addElementWithSorted(new Integer(100));

		ar->addElementWithSorted(new Integer(200));

		CHECK(ar->size() == (maxLoop + 9));

		isSorted(ar);
		releaseInternalObjects(ar);
	}
}


TEST(TestVmMemListSort, removeObjFalse){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	{
		VMemList<Integer, Integer::ValueCompare>* ar = new(vm) VMemList<Integer, Integer::ValueCompare>(vm, 8);
		__STP(ar);

		ar->addElement(new Integer(1));

		Integer val(2);
		bool result = ar->removeByObj(&val);
		CHECK(result == false)

		int size = ar->size();
		for(int i = 0; i != size; ++i){
			Integer* ptr = ar->get(i);
			delete ptr;
		}
	}
}

TEST(TestVmMemListSort, removeObjTrue){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	{
		VMemList<Integer, Integer::ValueCompare>* ar = new(vm) VMemList<Integer, Integer::ValueCompare>(vm, 8);
		__STP(ar);

		int maxLoop = 10;
		for(int i = 0; i != 10; ++i){
			Integer* pInt = new Integer(maxLoop - i);
			ar->addElement(pInt);
		}

		ar->addElementWithSorted(new Integer(11));
		ar->addElementWithSorted(new Integer(0));
		ar->addElementWithSorted(new Integer(5));
		ar->addElementWithSorted(new Integer(-1));
		ar->addElementWithSorted(new Integer(-1));
		ar->addElementWithSorted(new Integer(100));
		ar->addElementWithSorted(new Integer(100));

		ar->addElementWithSorted(new Integer(100));

		ar->addElementWithSorted(new Integer(200));

		Integer val(11);
		Integer* last = ar->search(&val);

		bool result = ar->removeByObj(&val);
		CHECK(result == true)

		delete last;

		CHECK(ar->size() == (maxLoop + 8));

		isSorted(ar);
		releaseInternalObjects(ar);
	}
}


