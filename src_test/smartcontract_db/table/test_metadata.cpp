/*
 * test_metadata.cpp
 *
 *  Created on: 2020/06/14
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "trx/scan/transaction_scan_result/ScanResultMetadata.h"

using codablecash::ScanResultMetadata;

using namespace alinous;
using namespace codablecash;


TEST_GROUP(TestMetadataGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};


TEST(TestMetadataGroup, construct){
	ScanResultMetadata metadata;

}
