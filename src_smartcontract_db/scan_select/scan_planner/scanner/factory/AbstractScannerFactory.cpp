/*
 * AbstractScannerFactory.cpp
 *
 *  Created on: 2020/08/28
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/AbstractScannerFactory.h"

#include "trx/transaction_scan_result/ScanResultMetadata.h"

namespace codablecash {

AbstractScannerFactory::AbstractScannerFactory(const ScanResultMetadata* metadata) {
	this->metadata = new ScanResultMetadata(*metadata);
}

AbstractScannerFactory::~AbstractScannerFactory() {
	delete this->metadata;
}

} /* namespace codablecash */
