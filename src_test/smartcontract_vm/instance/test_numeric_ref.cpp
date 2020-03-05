/*
 * test_numeric_ref.cpp
 *
 *  Created on: 2020/03/05
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "instance_ref/PrimitiveReference.h"
using namespace alinous;

TEST_GROUP(TestNumericRefGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestNumericRefGroup, long01){
	VirtualMachine vm(1024);

	int32_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, val);
	PrimitiveReference* ref2 = PrimitiveReference::createIntReference(&vm, val);
	int64_t ret = ref->getLongValue();

	CHECK(ret == 1);

	delete ref;
	delete ref2;
}

TEST(TestNumericRefGroup, long02){
	VirtualMachine vm(1024);

	int8_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createByteReference(&vm, val);
	PrimitiveReference* ref2 = PrimitiveReference::createIntReference(&vm, val);
	int64_t ret = ref->getLongValue();

	CHECK(ret == 1);

	delete ref;
	delete ref2;
}

TEST(TestNumericRefGroup, long03){
	VirtualMachine vm(1024);

	int16_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createShortReference(&vm, val);
	PrimitiveReference* ref2 = PrimitiveReference::createIntReference(&vm, val);
	int64_t ret = ref->getLongValue();

	CHECK(ret == 1);

	delete ref;
	delete ref2;
}

TEST(TestNumericRefGroup, long04){
	VirtualMachine vm(1024);

	int16_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createCharReference(&vm, val);
	PrimitiveReference* ref2 = PrimitiveReference::createIntReference(&vm, val);
	int64_t ret = ref->getLongValue();

	CHECK(ret == 1);

	delete ref;
	delete ref2;
}

