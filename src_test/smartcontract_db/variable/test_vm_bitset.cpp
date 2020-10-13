/*
 * test_vm_bitset.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_dom/DomVariableInstance.h"

#include "instance/instance_parts/VMemRawBitSet.h"

#include "base/StackRelease.h"

using namespace alinous;

TEST_GROUP(TestVmBitsetGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestVmBitsetGroup, case01){
	VirtualMachine vm(1024 * 10);

	VMemRawBitSet* bs = new VMemRawBitSet(&vm, 10);

	bs->set(2);
	bs->set(4);
	bs->set(6);
	bs->set(1100);

	int pos = 0;

	int count = 0;
	while(pos >= 0){
		pos = bs->nextSetBit(pos);
		if(pos < 0){
			break;
		}
		count++;
		pos++;
	}
	CHECK(count == 4);

	bs->clear(4);
	bs->clear(2000);
	pos = 0;
	count = 0;
	while(pos >= 0){
		pos = bs->nextSetBit(pos);
		if(pos < 0){
			break;
		}
		count++;
		pos++;
	}
	CHECK(count == 3);

	bs->clear();
	pos = 0;
	count = 0;
	while(pos >= 0){
		pos = bs->nextSetBit(pos);
		if(pos < 0){
			break;
		}
		count++;
		pos++;
	}
	CHECK(count == 0);

	delete bs;
}

TEST(TestVmBitsetGroup, case02){
	VirtualMachine vm(1024 * 10);

	VMemRawBitSet* bs = new VMemRawBitSet(&vm, 1024); __STP(bs);

	bs->set(400);
	bs->clear(400);

	CHECK(bs->nextSetBit(0) < 0);
}

TEST(TestVmBitsetGroup, case03){
	VirtualMachine vm(1024 * 10);

	VMemRawBitSet* bs = new VMemRawBitSet(&vm, 64); __STP(bs);

	bs->clear(5);
	bs->set(5);

	for(int i = 0; i != 64; ++i){
		int pos = bs->nextSetBit(i);

		if(i <= 5){
			CHECK(pos == 5);
		}
		else{
			CHECK(pos < 0);
		}
	}
}
