/*
 * TableScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_planner_scanner/TableScannerFactory.h"

namespace codablecash {

TableScannerFactory::TableScannerFactory(const ScanResultMetadata* metadata)
				: AbstractScannerFactory(metadata){

}

TableScannerFactory::~TableScannerFactory() {

}

} /* namespace codablecash */
