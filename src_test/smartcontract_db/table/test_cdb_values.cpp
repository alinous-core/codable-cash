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

#include "base_io/ByteBuffer.h"


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


