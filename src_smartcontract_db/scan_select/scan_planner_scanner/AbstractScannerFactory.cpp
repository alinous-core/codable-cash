/*
 * AbstractScannerFactory.cpp
 *
 *  Created on: 2020/08/28
 *      Author: iizuka
 */

#include "scan_select/scan_planner_scanner/AbstractScannerFactory.h"

#include "transaction_scan_result/ScanResultMetadata.h"

namespace codablecash {

AbstractScannerFactory::AbstractScannerFactory(const ScanResultMetadata* metadata) {
	this->metadata = new ScanResultMetadata(*metadata);
}

AbstractScannerFactory::~AbstractScannerFactory() {
	delete this->metadata;
}

} /* namespace codablecash */
