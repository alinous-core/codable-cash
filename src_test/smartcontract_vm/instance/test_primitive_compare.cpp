/*
 * test_primitive_compare.cpp
 *
 *  Created on: 2020/03/09
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "../VmTestUtils.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/RefereceFactory.h"

#include "instance/instance_gc/GcManager.h"

#include "instance/instance_ref/PrimitiveReference.h"

using namespace alinous;

TEST_GROUP(TestPrimitiveCompareGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestPrimitiveCompareGroup, case01){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createByteReference(&vm, 10);  __STP(left);
	PrimitiveReference* right = PrimitiveReference::createByteReference(&vm, 9);  __STP(right);

	int result = left->valueCompare(right);
	CHECK(result == 1);
}

TEST(TestPrimitiveCompareGroup, case02){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createShortReference(&vm, 10);  __STP(left);
	PrimitiveReference* right = PrimitiveReference::createShortReference(&vm, 9);  __STP(right);

	int result = left->valueCompare(right);
	CHECK(result == 1);
}

TEST(TestPrimitiveCompareGroup, case03){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createIntReference(&vm, 10);  __STP(left);
	PrimitiveReference* right = PrimitiveReference::createIntReference(&vm, 9);  __STP(right);

	int result = left->valueCompare(right);
	CHECK(result == 1);
}

TEST(TestPrimitiveCompareGroup, case04){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createLongReference(&vm, 10);  __STP(left);
	PrimitiveReference* right = PrimitiveReference::createLongReference(&vm, 9);  __STP(right);

	int result = left->valueCompare(right);
	CHECK(result == 1);
}


TEST(TestPrimitiveCompareGroup, case05){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createBoolReference(&vm, 10);  __STP(left);
	PrimitiveReference* right = PrimitiveReference::createBoolReference(&vm, 9);  __STP(right);

	int result = left->valueCompare(right);
	CHECK(result == -1);
}

TEST(TestPrimitiveCompareGroup, case06){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createBoolReference(&vm, 10);  __STP(left);

	int result = left->instValueCompare(nullptr);
	CHECK(result == -1);
}
