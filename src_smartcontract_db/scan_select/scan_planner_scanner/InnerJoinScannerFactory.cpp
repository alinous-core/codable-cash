/*
 * InnerJoinFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner_scanner/InnerJoinScannerFactory.h"

namespace codablecash {

InnerJoinScannerFactory::InnerJoinScannerFactory(const ScanResultMetadata* metadata)
			: AbstractJoinScannerFactory(metadata){

}

InnerJoinScannerFactory::~InnerJoinScannerFactory() {
}

IJoinLeftSource* InnerJoinScannerFactory::createScannerAsLeftSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
	// FIXME createScannerAsLeftSource
	return nullptr;
}

IJoinRightSource* InnerJoinScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
	return nullptr;
}

} /* namespace codablecash */
