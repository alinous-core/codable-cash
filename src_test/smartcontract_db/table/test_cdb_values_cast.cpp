/*
 * test_cdb_values_cast.cpp
 *
 *  Created on: 2020/09/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "engine/CdbException.h"

#include "table_record/CdbDataFactory.h"

#include "table_record_value/CdbByteValue.h"
#include "table_record_value/CdbShortValue.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbLongValue.h"
#include "table_record_value/CdbStringValue.h"
#include "table_record_value/VmInstanceValueConverter.h"
#include "table_record_value/AbstractCdbValue.h"
#include "table_record_value/CdbValueCaster.h"
#include "table_record_value/CdbValueCastException.h"

#include "table_record/CdbRecord.h"
using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestCdbValuesCastGroup) {
	TEST_SETUP() {
	}
	TEST_TEARDOWN() {
	}
};

TEST(TestCdbValuesCastGroup, testException01){
	testException<CdbValueCastException>();
}

TEST(TestCdbValuesCastGroup, case01){
	CHECK(CdbValueCaster::convertFromString(nullptr, 1) == nullptr);
}

TEST(TestCdbValuesCastGroup, case02){
	UnicodeString str(L"100");

	CdbException* ex = nullptr;
	try{
		AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, 111); __STP(value);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestCdbValuesCastGroup, convertFromStringByte01){
	UnicodeString str(L"100");
	uint8_t cdbValueType = AbstractCdbValue::TYPE_BYTE;

	AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int8_t val = dynamic_cast<CdbByteValue*>(value)->getValue();
	CHECK(val == 100);
}

TEST(TestCdbValuesCastGroup, convertFromStringByte02){
	UnicodeString str(L"10000000000000000000");
	uint8_t cdbValueType = AbstractCdbValue::TYPE_BYTE;

	CdbValueCastException* ex = nullptr;
	try{
		AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, cdbValueType); __STP(value);
	}catch(CdbValueCastException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestCdbValuesCastGroup, convertFromStringShort01){
	UnicodeString str(L"100");
	uint8_t cdbValueType = AbstractCdbValue::TYPE_SHORT;

	AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int16_t val = dynamic_cast<CdbShortValue*>(value)->getValue();
	CHECK(val == 100);
}

TEST(TestCdbValuesCastGroup, convertFromStringShort02){
	UnicodeString str(L"10000000000000000000");
	uint8_t cdbValueType = AbstractCdbValue::TYPE_SHORT;

	CdbValueCastException* ex = nullptr;
	try{
		AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, cdbValueType); __STP(value);
	}catch(CdbValueCastException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestCdbValuesCastGroup, convertFromStringInt01){
	UnicodeString str(L"100");
	uint8_t cdbValueType = AbstractCdbValue::TYPE_INT;

	AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int32_t val = dynamic_cast<CdbIntValue*>(value)->getValue();
	CHECK(val == 100);
}

TEST(TestCdbValuesCastGroup, convertFromStringInt02){
	UnicodeString str(L"10000000000000000000");
	uint8_t cdbValueType = AbstractCdbValue::TYPE_INT;

	CdbValueCastException* ex = nullptr;
	try{
		AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, cdbValueType); __STP(value);
	}catch(CdbValueCastException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestCdbValuesCastGroup, convertFromStringLong01){
	UnicodeString str(L"100");
	uint8_t cdbValueType = AbstractCdbValue::TYPE_LONG;

	AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int64_t val = dynamic_cast<CdbLongValue*>(value)->getValue();
	CHECK(val == 100);
}

TEST(TestCdbValuesCastGroup, convertFromStringString01){
	UnicodeString str(L"10000000000000000000");
	uint8_t cdbValueType = AbstractCdbValue::TYPE_STRING;

	AbstractCdbValue* value = CdbValueCaster::convertFromString(&str, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	const UnicodeString* ret = dynamic_cast<CdbStringValue*>(value)->getValue();
	CHECK(str.equals(ret));
}

TEST(TestCdbValuesCastGroup, testcast01){
	CHECK(CdbValueCaster::cast(nullptr, 1) == nullptr);
}

TEST(TestCdbValuesCastGroup, testCastByte01){
	CdbByteValue base(10);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_STRING;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	const UnicodeString* ret = dynamic_cast<CdbStringValue*>(value)->getValue();
	UnicodeString str(L"10");
	CHECK(str.equals(ret));
}

TEST(TestCdbValuesCastGroup, testCastByte02){
	uint8_t v = 10;
	CdbByteValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_BYTE;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int8_t ret = dynamic_cast<CdbByteValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastByte03){
	uint8_t v = 10;
	CdbByteValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_SHORT;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int16_t ret = dynamic_cast<CdbShortValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastByte04){
	uint8_t v = 10;
	CdbByteValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_INT;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int32_t ret = dynamic_cast<CdbIntValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastByte05){
	uint8_t v = 10;
	CdbByteValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_LONG;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int64_t ret = dynamic_cast<CdbLongValue*>(value)->getValue();
	CHECK(ret == v);
}

///////////////////////////////////////////////

TEST(TestCdbValuesCastGroup, testCastShort01){
	CdbShortValue base(10);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_STRING;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	const UnicodeString* ret = dynamic_cast<CdbStringValue*>(value)->getValue();
	UnicodeString str(L"10");
	CHECK(str.equals(ret));
}

TEST(TestCdbValuesCastGroup, testCastShort02){
	uint8_t v = 10;
	CdbShortValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_BYTE;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int8_t ret = dynamic_cast<CdbByteValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastShort03){
	uint8_t v = 10;
	CdbShortValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_SHORT;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int16_t ret = dynamic_cast<CdbShortValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastShort04){
	uint8_t v = 10;
	CdbShortValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_INT;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int32_t ret = dynamic_cast<CdbIntValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastShort05){
	uint8_t v = 10;
	CdbShortValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_LONG;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int64_t ret = dynamic_cast<CdbLongValue*>(value)->getValue();
	CHECK(ret == v);
}

///////////////////////////////////////////////

TEST(TestCdbValuesCastGroup, testCastInt01){
	CdbIntValue base(10);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_STRING;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	const UnicodeString* ret = dynamic_cast<CdbStringValue*>(value)->getValue();
	UnicodeString str(L"10");
	CHECK(str.equals(ret));
}

TEST(TestCdbValuesCastGroup, testCastInt02){
	uint8_t v = 10;
	CdbIntValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_BYTE;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int8_t ret = dynamic_cast<CdbByteValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastInt03){
	uint8_t v = 10;
	CdbIntValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_SHORT;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int16_t ret = dynamic_cast<CdbShortValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastInt04){
	uint8_t v = 10;
	CdbIntValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_INT;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int32_t ret = dynamic_cast<CdbIntValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastInt05){
	uint8_t v = 10;
	CdbIntValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_LONG;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int64_t ret = dynamic_cast<CdbLongValue*>(value)->getValue();
	CHECK(ret == v);
}

///////////////////////////////////////////////

TEST(TestCdbValuesCastGroup, testCastLong01){
	CdbLongValue base(10);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_STRING;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	const UnicodeString* ret = dynamic_cast<CdbStringValue*>(value)->getValue();
	UnicodeString str(L"10");
	CHECK(str.equals(ret));
}

TEST(TestCdbValuesCastGroup, testCastLong02){
	uint8_t v = 10;
	CdbLongValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_BYTE;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int8_t ret = dynamic_cast<CdbByteValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastLong03){
	uint8_t v = 10;
	CdbLongValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_SHORT;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int16_t ret = dynamic_cast<CdbShortValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastLong04){
	uint8_t v = 10;
	CdbLongValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_INT;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int32_t ret = dynamic_cast<CdbIntValue*>(value)->getValue();
	CHECK(ret == v);
}

TEST(TestCdbValuesCastGroup, testCastLong05){
	uint8_t v = 10;
	CdbLongValue base(v);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_LONG;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int64_t ret = dynamic_cast<CdbLongValue*>(value)->getValue();
	CHECK(ret == v);
}

///////////////////////////////////////////////
TEST(TestCdbValuesCastGroup, testCastString01){
	UnicodeString str(L"100");
	CdbStringValue base(&str);
	uint8_t cdbValueType = AbstractCdbValue::TYPE_LONG;

	AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	CHECK(value->getType() == cdbValueType);

	int64_t ret = dynamic_cast<CdbLongValue*>(value)->getValue();
	CHECK(ret == 100);
}

TEST(TestCdbValuesCastGroup, testCastError01){
	CdbRecord base;
	uint8_t cdbValueType = AbstractCdbValue::TYPE_LONG;

	CdbException* ex = nullptr;
	try{
		AbstractCdbValue* value = CdbValueCaster::cast(&base, cdbValueType); __STP(value);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}
