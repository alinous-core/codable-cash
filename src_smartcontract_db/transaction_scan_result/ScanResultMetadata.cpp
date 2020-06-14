/*
 * ScanResultMetadata.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "transaction_scan_result/ScanResultMetadata.h"
#include "transaction_scan_result/ScanResultFieldMetadata.h"

#include "base/UnicodeString.h"


namespace codablecash {

ScanResultMetadata::ScanResultMetadata() {
	this->map = new HashMap<UnicodeString, ScanResultFieldMetadata>();
}

ScanResultMetadata::~ScanResultMetadata() {
	delete this->map;
}

} /* namespace codablecash */
