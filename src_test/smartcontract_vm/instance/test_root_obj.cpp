/*
 * test_root_obj.cpp
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
#include "instance/instance_ref/VmRootReference.h"

using namespace alinous;

TEST_GROUP(TestRootObjectGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestRootObjectGroup, test01) {
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm); __STP(root);
	CHECK(root->wrap(nullptr, &vm) == nullptr)

	AnalyzedType at = root->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_NONE);
}

TEST(TestRootObjectGroup, test02) {
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm); __STP(root);
	CHECK(root->getInstReferences() == root->getReferences())
}

TEST(TestRootObjectGroup, test03) {
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm); __STP(root);
	CHECK(root->instIsNull() == root->isNull())
}

TEST(TestRootObjectGroup, test04) {
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm); __STP(root);
	CHECK(root->instIsPrimitive() == root->isPrimitive())
}

TEST(TestRootObjectGroup, test05) {
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm); __STP(root);
	CHECK(root->instHashCode() == root->hashCode())
}

TEST(TestRootObjectGroup, test06) {
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm); __STP(root);
	CHECK(root->instValueCompare(nullptr) == 0)
}

TEST(TestRootObjectGroup, test07) {
	VirtualMachine vm(1024 * 10);

	VmRootReference* root = new(&vm) VmRootReference(&vm); __STP(root);
	UnicodeString name(L"name");
	AbstractExtObject* extObj = root->instToClassExtObject(&name, nullptr);

	delete extObj;
}
