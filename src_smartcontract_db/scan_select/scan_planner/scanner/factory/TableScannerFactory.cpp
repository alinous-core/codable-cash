/*
 * TableScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/TableScannerFactory.h"

namespace codablecash {

TableScannerFactory::TableScannerFactory(const ScanResultMetadata* metadata)
				: AbstractScannerFactory(metadata){

}

TableScannerFactory::~TableScannerFactory() {

}

} /* namespace codablecash */
