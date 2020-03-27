/*
 * test_primitive.cpp
 *
 *  Created on: 2020/03/27
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "../VmTestUtils.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref/RefereceFactory.h"

#include "instance_gc/GcManager.h"

#include "instance_ref/PrimitiveReference.h"

using namespace alinous;

TEST_GROUP(TestPrimitiveGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestPrimitiveGroup, test01){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createIntReference(&vm, 10);  __STP(left);
	CHECK(left->instIsNull() == false)
}

TEST(TestPrimitiveGroup, test02){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createIntReference(&vm, 10);  __STP(left);
	CHECK(left->getInstType() == left->getType());
}

TEST(TestPrimitiveGroup, test03){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createIntReference(&vm, 10);  __STP(left);
	CHECK(left->instHashCode() == left->hashCode());
}

TEST(TestPrimitiveGroup, test04){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createIntReference(&vm, 10);  __STP(left);
	CHECK(left->getInstReferences() == left->getReferences());
}

TEST(TestPrimitiveGroup, test05){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createIntReference(&vm, 10);  __STP(left);
	PrimitiveReference* right = left->copy(&vm);

	CHECK(left->instValueCompare(right) == 0);
}

TEST(TestPrimitiveGroup, test06){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createIntReference(&vm, 10);  __STP(left);

	UnicodeString name(L"name");
	AbstractExtObject* extObj = left->instToClassExtObject(&name, nullptr);

	delete extObj;
}
