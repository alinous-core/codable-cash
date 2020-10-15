/*
 * test_cdb_values_cast_default.cpp
 *
 *  Created on: 2020/09/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "engine/CdbException.h"

#include "schema_table/record/table_record/CdbDataFactory.h"

#include "schema_table/record/table_record_value/CdbByteValue.h"
#include "schema_table/record/table_record_value/CdbShortValue.h"
#include "schema_table/record/table_record_value/CdbIntValue.h"
#include "schema_table/record/table_record_value/CdbLongValue.h"
#include "schema_table/record/table_record_value/CdbStringValue.h"
#include "schema_table/record/table_record_value/VmInstanceValueConverter.h"
#include "schema_table/record/table_record_value/AbstractCdbValue.h"
#include "schema_table/record/table_record_value/CdbValueCaster.h"
#include "schema_table/record/table_record_value/CdbValueCastException.h"

#include "schema_table/record/table_record/CdbRecord.h"
using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestCdbValuesCastDefaultGroup) {
	TEST_SETUP() {
	}
	TEST_TEARDOWN() {
	}
};

TEST(TestCdbValuesCastDefaultGroup, case01){
	uint8_t cdbType = AbstractCdbValue::TYPE_BYTE;

	AbstractCdbValue* value = CdbValueCaster::getDefaultValue(cdbType); __STP(value);
	CHECK(value->getType() == cdbType);
}

TEST(TestCdbValuesCastDefaultGroup, case02){
	uint8_t cdbType = AbstractCdbValue::TYPE_SHORT;

	AbstractCdbValue* value = CdbValueCaster::getDefaultValue(cdbType); __STP(value);
	CHECK(value->getType() == cdbType);
}

TEST(TestCdbValuesCastDefaultGroup, case03){
	uint8_t cdbType = AbstractCdbValue::TYPE_INT;

	AbstractCdbValue* value = CdbValueCaster::getDefaultValue(cdbType); __STP(value);
	CHECK(value->getType() == cdbType);
}

TEST(TestCdbValuesCastDefaultGroup, case04){
	uint8_t cdbType = AbstractCdbValue::TYPE_LONG;

	AbstractCdbValue* value = CdbValueCaster::getDefaultValue(cdbType); __STP(value);
	CHECK(value->getType() == cdbType);
}

TEST(TestCdbValuesCastDefaultGroup, case05){
	uint8_t cdbType = AbstractCdbValue::TYPE_STRING;

	AbstractCdbValue* value = CdbValueCaster::getDefaultValue(cdbType); __STP(value);
	CHECK(value->getType() == cdbType);
}

TEST(TestCdbValuesCastDefaultGroup, case06){
	CdbException* ex = nullptr;
	try{
		AbstractCdbValue* value = CdbValueCaster::getDefaultValue(111); __STP(value);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}
