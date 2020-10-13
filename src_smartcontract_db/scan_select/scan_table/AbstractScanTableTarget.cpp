/*
 * AbstractScanTableTarget.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "scan_select/scan_table/AbstractScanTableTarget.h"

#include "transaction_scan_result/ScanResultMetadata.h"

namespace codablecash {

AbstractScanTableTarget::AbstractScanTableTarget() {
	this->metadata = nullptr;
}

AbstractScanTableTarget::~AbstractScanTableTarget() {
	delete this->metadata;
}

} /* namespace codablecash */
