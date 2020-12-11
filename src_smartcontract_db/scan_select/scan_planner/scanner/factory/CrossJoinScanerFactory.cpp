/*
 * CrossJoinScanerTarget.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/CrossJoinScanerFactory.h"

namespace codablecash {

CrossJoinScanerFactory::CrossJoinScanerFactory(const ScanResultMetadata* metadata, const AbstractScanCondition* joinCondition)
			: AbstractJoinScannerFactory(metadata, joinCondition) {

}

CrossJoinScanerFactory::~CrossJoinScanerFactory() {

}

IJoinLeftSource* CrossJoinScanerFactory::createScannerAsLeftSource(VirtualMachine* vm, SelectScanPlanner* planner) {
	// FIXME createScannerAsLeftSource
	return nullptr;
}

IJoinRightSource* CrossJoinScanerFactory::createScannerAsRightSource(VirtualMachine* vm, SelectScanPlanner* planner) {
	return nullptr;
}

} /* namespace codablecash */
