/*
 * test_ext_objects.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "instance/VmInstanceTypesConst.h"

using namespace alinous;


TEST_GROUP(TestExtObjects) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestExtObjects, constructObj){
	UnicodeString name("main");
	ExtClassObject obj(&name);
}

TEST(TestExtObjects, classobjadd){
	UnicodeString name("main");
	ExtClassObject obj(&name);

	UnicodeString count("count");
	ExtPrimitiveObject* intOnj = ExtPrimitiveObject::createIntObject(&count, 1);
	obj.add(intOnj);

	uint8_t type = obj.getType();
	CHECK(type == VmInstanceTypesConst::ISNT_OBJ);
}

TEST(TestExtObjects, constructPrimitive){
	UnicodeString name("main");
	ExtPrimitiveObject* obj = ExtPrimitiveObject::createIntObject(&name, 1); __STP(obj);

	int32_t v = obj->getIntValue();
	CHECK(v == 1);

	const UnicodeString* str = obj->getName();
	CHECK(name.equals(str))

	uint8_t type = obj->getType();
	CHECK(type == VmInstanceTypesConst::REF_INT);
}

TEST(TestExtObjects, boolPrimitive){
	UnicodeString name("main");
	ExtPrimitiveObject* obj = ExtPrimitiveObject::createBoolObject(&name, 1); __STP(obj);

	bool ret = obj->getBoolValue();
	CHECK(ret == true);

	uint8_t type = obj->getType();
	CHECK(type == VmInstanceTypesConst::REF_BOOL);
}

TEST(TestExtObjects, boolPrimitive2){
	UnicodeString name("main");
	ExtPrimitiveObject* obj = ExtPrimitiveObject::createBoolObject(&name, 0); __STP(obj);

	bool ret = obj->getBoolValue();
	CHECK(ret == false);

	uint8_t type = obj->getType();
	CHECK(type == VmInstanceTypesConst::REF_BOOL);
}

TEST(TestExtObjects, bytePrimitive){
	UnicodeString name("main");
	ExtPrimitiveObject* obj = ExtPrimitiveObject::createByteObject(&name, 1); __STP(obj);

	bool ret = obj->getByteValue();
	CHECK(ret == 1);

	uint8_t type = obj->getType();
	CHECK(type == VmInstanceTypesConst::REF_BYTE);
}

TEST(TestExtObjects, bytePrimitive2){
	UnicodeString name("main");
	int8_t ch = 125;
	ExtPrimitiveObject* obj = ExtPrimitiveObject::createByteObject(&name, ch); __STP(obj);

	int8_t ret = obj->getByteValue();
	CHECK(ret == 125);

	uint8_t type = obj->getType();
	CHECK(type == VmInstanceTypesConst::REF_BYTE);
}

TEST(TestExtObjects, charPrimitive){
	UnicodeString name("main");
	wchar_t ch = L'A';
	ExtPrimitiveObject* obj = ExtPrimitiveObject::createCharObject(&name, ch); __STP(obj);

	wchar_t ret = obj->getCharValue();
	CHECK(ret == ch);

	uint8_t type = obj->getType();
	CHECK(type == VmInstanceTypesConst::REF_CHAR);
}

TEST(TestExtObjects, shortPrimitive){
	UnicodeString name("main");
	short ch = L'A';
	ExtPrimitiveObject* obj = ExtPrimitiveObject::createShortObject(&name, ch); __STP(obj);

	short ret = obj->getShortValue();
	CHECK(ret == ch);

	uint8_t type = obj->getType();
	CHECK(type == VmInstanceTypesConst::REF_SHORT);
}

TEST(TestExtObjects, longPrimitive){
	UnicodeString name("main");
	int64_t value = 12345678901234;
	ExtPrimitiveObject* obj = ExtPrimitiveObject::createLongObject(&name, value); __STP(obj);

	int64_t ret = obj->getLongValue();
	CHECK(ret == value);

	uint8_t type = obj->getType();
	CHECK(type == VmInstanceTypesConst::REF_LONG);
}
