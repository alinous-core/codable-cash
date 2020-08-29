/*
 * AbstractJoinScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_planner_scanner/AbstractJoinScannerFactory.h"


namespace codablecash {

AbstractJoinScannerFactory::AbstractJoinScannerFactory(const ScanResultMetadata* metadata)
					: AbstractScannerFactory(metadata) {

}

AbstractJoinScannerFactory::~AbstractJoinScannerFactory() {

}

} /* namespace codablecash */
