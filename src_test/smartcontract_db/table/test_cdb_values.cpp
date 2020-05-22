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

#include "table_record_value/CdbByteValue.h"
#include "table_record_value/CdbShortValue.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbLongValue.h"
#include "table_record_value/CdbStringValue.h"

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
}

TEST(TestCdbValuesGroup, CdbShortValue){
	CdbShortValue value;
}

TEST(TestCdbValuesGroup, CdbIntValue){
	CdbIntValue value;
}

TEST(TestCdbValuesGroup, CdbLongValue){
	CdbLongValue value;
}

TEST(TestCdbValuesGroup, CdbString){
	CdbStringValue value;
}


