/*
 * LeftJoinScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_planner_scanner/LeftJoinScannerFactory.h"

namespace codablecash {

LeftJoinScannerFactory::LeftJoinScannerFactory(const ScanResultMetadata* metadata)
				: AbstractJoinScannerFactory(metadata){

}

LeftJoinScannerFactory::~LeftJoinScannerFactory() {

}

IJoinLeftSource* LeftJoinScannerFactory::createScannerAsLeftSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
}

IJoinRightSource* LeftJoinScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
}


} /* namespace codablecash */
