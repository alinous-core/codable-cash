/*
 * test_ext_objects.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"
#include "ext_binary/ExtStringClass.h"
#include "ext_binary/ExtNullPtrObject.h"

#include "instance/VmInstanceTypesConst.h"

#include "ext_binary/ExtExceptionObject.h"

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
	CHECK(type == VmInstanceTypesConst::INST_OBJ);
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

TEST(TestExtObjects, string01){
	UnicodeString name(L"name");
	ExtStringClass extstr(&name);
}

TEST(TestExtObjects, classObj01){
	UnicodeString name(L"name");
	ExtClassObject obj(&name);

	UnicodeString exname(L"dummyEx");
	ExtExceptionObject* exobj = obj.getExtExceptionObject(&exname);
	CHECK(exobj == nullptr);
}

TEST(TestExtObjects, extExceptionCopy){
	UnicodeString name(L"name");
	ExtExceptionObject exobj(&name);

	ExtExceptionObject* exobj2 = dynamic_cast<ExtExceptionObject*>(exobj.copy()); __STP(exobj2);
	CHECK(exobj2 != nullptr)
}

TEST(TestExtObjects, nullObj01){
	UnicodeString name(L"name");
	ExtNullPtrObject obj(&name, 0);

	ExtNullPtrObject* obj1 = dynamic_cast<ExtNullPtrObject*>(obj.copy()); __STP(obj1);
	CHECK(obj1 != nullptr)
}
