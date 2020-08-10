/*
 * test_cdb_values.cpp
 *
 *  Created on: 2020/05/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/File.h"
#include "base/StackRelease.h"

#include "engine/CdbException.h"
#include "engine/CdbBinaryObject.h"

#include "table_record/CdbDataFactory.h"

#include "table_record_value/CdbByteValue.h"
#include "table_record_value/CdbShortValue.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbLongValue.h"
#include "table_record_value/CdbStringValue.h"
#include "table_record_value/VmInstanceValueConverter.h"

#include "base_io/ByteBuffer.h"

#include "vm/VirtualMachine.h"

#include "instance_ref/VmRootReference.h"

#include "instance_ref/PrimitiveReference.h"
using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestCdbValuesGroup) {
	TEST_SETUP() {
	}
	TEST_TEARDOWN() {
	}
};

TEST(TestCdbValuesGroup, CdbByteValue){
	CdbByteValue value;
	CdbByteValue value2(value);

	int size = value.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	value.toBinary(buff);

	buff->position(0);
	CdbDataFactory factory;

	IBlockObject* obj = factory.makeDataFromBinary(buff); __STP(obj);

	CdbByteValue* bv = dynamic_cast<CdbByteValue*>(obj);
	CHECK(bv->getValue() == value2.getValue())
}

TEST(TestCdbValuesGroup, CdbShortValue){
	CdbShortValue value;
	CdbShortValue value2(value);

	int size = value.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	value.toBinary(buff);

	buff->position(0);
	CdbDataFactory factory;

	IBlockObject* obj = factory.makeDataFromBinary(buff); __STP(obj);

	CdbShortValue* bv = dynamic_cast<CdbShortValue*>(obj);
	CHECK(bv->getValue() == value2.getValue())
}

TEST(TestCdbValuesGroup, CdbIntValue){
	CdbIntValue value;
	CdbIntValue value2(value);

	int size = value.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	value.toBinary(buff);

	buff->position(0);
	CdbDataFactory factory;

	IBlockObject* obj = factory.makeDataFromBinary(buff); __STP(obj);

	CdbIntValue* bv = dynamic_cast<CdbIntValue*>(obj);
	CHECK(bv->getValue() == value2.getValue())
}

TEST(TestCdbValuesGroup, CdbLongValue){
	CdbLongValue value;
	CdbLongValue value2(value);

	int size = value.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	value.toBinary(buff);

	buff->position(0);
	CdbDataFactory factory;

	IBlockObject* obj = factory.makeDataFromBinary(buff); __STP(obj);

	CdbLongValue* bv = dynamic_cast<CdbLongValue*>(obj);
	CHECK(bv->getValue() == value2.getValue())
}

TEST(TestCdbValuesGroup, CdbString){
	UnicodeString hello(L"hello");
	CdbStringValue value(&hello);
	CdbStringValue value2(value);

	int size = value.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	value.toBinary(buff);

	buff->position(0);
	CdbDataFactory factory;

	IBlockObject* obj = factory.makeDataFromBinary(buff); __STP(obj);

	CdbStringValue* bv = dynamic_cast<CdbStringValue*>(obj);
	CHECK(value2.getValue()->equals(bv->getValue()));
}

TEST(TestCdbValuesGroup, dataFactoryError){
	int size = 10;
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	buff->put(100);
	buff->position(0);

	CdbDataFactory factory;
	CdbException* ex = nullptr;
	try{
		factory.makeDataFromBinary(buff);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestCdbValuesGroup, toCdbValue01){
	AbstractCdbValue* value = VmInstanceValueConverter::toCdbValue(nullptr, 0);
	CHECK(value == nullptr)
}

TEST(TestCdbValuesGroup, toCdbValue02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	CdbException* ex = nullptr;
	try{
		VmRootReference* ref = new(vm) VmRootReference(vm); __STP(ref);
		AbstractCdbValue* value = VmInstanceValueConverter::toCdbValue(ref, 0);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestCdbValuesGroup, toCdbValue03){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	CdbException* ex = nullptr;
	try{
		PrimitiveReference* ref = PrimitiveReference::createByteReference(vm, 1); __STP(ref);
		AbstractCdbValue* value = VmInstanceValueConverter::toCdbValue(ref, 0);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestCdbValuesGroup, toCdbValue04){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	PrimitiveReference* ref = PrimitiveReference::createLongReference(vm, 1); __STP(ref);
	AbstractCdbValue* avalue = VmInstanceValueConverter::toCdbValue(ref, AbstractCdbValue::TYPE_BYTE); __STP(avalue);

	CdbByteValue* value = dynamic_cast<CdbByteValue*>(avalue);

	CHECK(value->getValue() == 1)
}

TEST(TestCdbValuesGroup, toCdbValue05){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	PrimitiveReference* ref = PrimitiveReference::createLongReference(vm, 1); __STP(ref);
	AbstractCdbValue* avalue = VmInstanceValueConverter::toCdbValue(ref, AbstractCdbValue::TYPE_SHORT); __STP(avalue);

	CdbShortValue* value = dynamic_cast<CdbShortValue*>(avalue);

	CHECK(value->getValue() == 1)
}

TEST(TestCdbValuesGroup, toCdbValue06){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	PrimitiveReference* ref = PrimitiveReference::createLongReference(vm, 1); __STP(ref);
	AbstractCdbValue* avalue = VmInstanceValueConverter::toCdbValue(ref, AbstractCdbValue::TYPE_LONG); __STP(avalue);

	CdbLongValue* value = dynamic_cast<CdbLongValue*>(avalue);

	CHECK(value->getValue() == 1)
}
