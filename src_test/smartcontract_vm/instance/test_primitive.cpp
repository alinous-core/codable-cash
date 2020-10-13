/*
 * test_primitive.cpp
 *
 *  Created on: 2020/03/27
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

TEST(TestPrimitiveGroup, test07){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createIntReference(&vm, 10);  __STP(left);

	AnalyzedType at = left->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_INT);
}

TEST(TestPrimitiveGroup, test08){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createBoolReference(&vm, 10);  __STP(left);

	AnalyzedType at = left->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestPrimitiveGroup, test09){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createByteReference(&vm, 10);  __STP(left);

	AnalyzedType at = left->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_BYTE);
}

TEST(TestPrimitiveGroup, test10){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createCharReference(&vm, 10);  __STP(left);

	AnalyzedType at = left->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_CHAR);
}

TEST(TestPrimitiveGroup, test11){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createShortReference(&vm, 10);  __STP(left);

	AnalyzedType at = left->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_SHORT);
}

TEST(TestPrimitiveGroup, test12){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createLongReference(&vm, 10);  __STP(left);

	AnalyzedType at = left->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_LONG);
}

TEST(TestPrimitiveGroup, test13){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createBoolReference(&vm, 0);  __STP(left);

	AnalyzedType at = left->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);

	UnicodeString t(L"false");
	const UnicodeString* str = left->toString();

	CHECK(t.equals(str));
}

TEST(TestPrimitiveGroup, test14){
	VirtualMachine vm(1024 * 10);

	PrimitiveReference* left = PrimitiveReference::createBoolReference(&vm, 1);  __STP(left);

	AnalyzedType at = left->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);

	UnicodeString t(L"true");
	const UnicodeString* str = left->toString();

	CHECK(t.equals(str));
}

