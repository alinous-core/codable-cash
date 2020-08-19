/*
 * test_scan_columns_part.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "scan_columns/AllScanColumns.h"
#include "scan_columns/ScanColumn.h"


using namespace codablecash;

TEST_GROUP(TestScanColumnsPartGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};


TEST(TestScanColumnsPartGroup, case01){
	AllScanColumns cols;
}

TEST(TestScanColumnsPartGroup, case02){
	ScanColumn col;
	const UnicodeString t(L"t");

	col.setAsName(&t);

}
