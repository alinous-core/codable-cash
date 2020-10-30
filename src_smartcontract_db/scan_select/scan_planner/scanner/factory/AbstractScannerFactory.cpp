/*
 * AbstractScannerFactory.cpp
 *
 *  Created on: 2020/08/28
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/AbstractScannerFactory.h"

#include "trx/scan/transaction_scan_result/ScanResultMetadata.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

namespace codablecash {

AbstractScannerFactory::AbstractScannerFactory(const ScanResultMetadata* metadata) {
	this->metadata = new ScanResultMetadata(*metadata);
	this->filterCondition = nullptr;
}

AbstractScannerFactory::~AbstractScannerFactory() {
	delete this->metadata;
	delete this->filterCondition;
}

void AbstractScannerFactory::setFilterCondition(const AbstractScanCondition* filterCondition) noexcept {
	if(filterCondition != nullptr){
		this->filterCondition = filterCondition->cloneCondition();
	}
}

} /* namespace codablecash */
