/*
 * AbstractJoinScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/AbstractJoinScannerFactory.h"

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"

namespace codablecash {

AbstractJoinScannerFactory::AbstractJoinScannerFactory(const ScanResultMetadata* metadata)
					: AbstractScannerFactory(metadata) {
	this->leftFactory = nullptr;
	this->rightFactory = nullptr;
	this->joinCandidate = nullptr;
}

AbstractJoinScannerFactory::~AbstractJoinScannerFactory() {
	delete this->leftFactory;
	delete this->rightFactory;
	delete this->joinCandidate;
}

void AbstractJoinScannerFactory::setLeft(AbstractScannerFactory* factory) noexcept {
	this->leftFactory = factory;
}

void AbstractJoinScannerFactory::setRight(AbstractScannerFactory* factory) noexcept {
	this->rightFactory = factory;
}

void AbstractJoinScannerFactory::setJoinCandidate(const AbstractJoinCandidate* joinCandidate) noexcept {
	this->joinCandidate = joinCandidate->copy();
}

} /* namespace codablecash */
