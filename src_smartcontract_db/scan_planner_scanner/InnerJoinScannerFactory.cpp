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

IJoinLeftSource* InnerJoinScannerFactory::createScannerAsLeftSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
}

IJoinRightSource* InnerJoinScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
}

} /* namespace codablecash */
