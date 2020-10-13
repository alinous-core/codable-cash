/*
 * test_numeric_ref.cpp
 *
 *  Created on: 2020/03/05
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "ext_binary/ExtPrimitiveObject.h"
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

TEST(TestNumericRefGroup, short01){
	VirtualMachine vm(1024);

	int16_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createByteReference(&vm, val);
	PrimitiveReference* ref2 = PrimitiveReference::createByteReference(&vm, val);
	int64_t ret = ref->getShortValue();

	CHECK(ret == 1);

	delete ref;
	delete ref2;
}

TEST(TestNumericRefGroup, char01){
	VirtualMachine vm(1024);

	int16_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createByteReference(&vm, val);
	PrimitiveReference* ref2 = PrimitiveReference::createByteReference(&vm, val);
	int64_t ret = ref->getCharValue();

	CHECK(ret == 1);

	delete ref;
	delete ref2;
}

TEST(TestNumericRefGroup, createBool){
	VirtualMachine vm(1024);

	int16_t val = 1;
	int16_t val2 = 0;
	PrimitiveReference* ref = PrimitiveReference::createBoolReference(&vm, val);
	PrimitiveReference* ref2 = PrimitiveReference::createBoolReference(&vm, val2);

	ref2->substitute(ref, &vm);

	CHECK(ref2->getIntValue() == 1);

	delete ref;
	delete ref2;
}

TEST(TestNumericRefGroup, createBoolExt){
	VirtualMachine vm(1024);

	int16_t val = 1;
	PrimitiveReference* ref = PrimitiveReference::createBoolReference(&vm, val);

	UnicodeString name(L"name");
	AbstractExtObject* ext = ref->toClassExtObject(&name, nullptr); __STP(ext);

	CHECK(ext != nullptr);
	ExtPrimitiveObject* extBool = dynamic_cast<ExtPrimitiveObject*>(ext);
	CHECK(extBool->getBoolValue());

	delete ref;
}

TEST(TestNumericRefGroup, createBoolExt2){
	VirtualMachine vm(1024);

	int16_t val = 0;
	PrimitiveReference* ref = PrimitiveReference::createBoolReference(&vm, val);

	UnicodeString name(L"name");
	AbstractExtObject* ext = ref->toClassExtObject(&name, nullptr); __STP(ext);

	CHECK(ext != nullptr);
	ExtPrimitiveObject* extBool = dynamic_cast<ExtPrimitiveObject*>(ext);
	CHECK(!extBool->getBoolValue());

	delete ref;
}

