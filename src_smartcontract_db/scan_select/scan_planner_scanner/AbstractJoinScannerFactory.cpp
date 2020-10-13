/*
 * AbstractJoinScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner_scanner/AbstractJoinScannerFactory.h"

namespace codablecash {

AbstractJoinScannerFactory::AbstractJoinScannerFactory(const ScanResultMetadata* metadata)
					: AbstractScannerFactory(metadata) {
	this->leftFactory = nullptr;
	this->rightFactory = nullptr;
}

AbstractJoinScannerFactory::~AbstractJoinScannerFactory() {
	delete this->leftFactory;
	delete this->rightFactory;
}

void AbstractJoinScannerFactory::setLeft(AbstractScannerFactory* factory) noexcept {
	this->leftFactory = factory;
}

void AbstractJoinScannerFactory::setRight(AbstractScannerFactory* factory) noexcept {
	this->rightFactory = factory;
}

} /* namespace codablecash */
