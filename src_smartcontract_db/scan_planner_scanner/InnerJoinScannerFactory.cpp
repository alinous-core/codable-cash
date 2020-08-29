/*
 * InnerJoinFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_planner_scanner/InnerJoinScannerFactory.h"

namespace codablecash {

InnerJoinScannerFactory::InnerJoinScannerFactory(const ScanResultMetadata* metadata)
			: AbstractJoinScannerFactory(metadata){

}

InnerJoinScannerFactory::~InnerJoinScannerFactory() {
}

} /* namespace codablecash */
