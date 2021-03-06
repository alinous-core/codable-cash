/*
 * InnerJoinFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/InnerJoinScannerFactory.h"

namespace codablecash {

InnerJoinScannerFactory::InnerJoinScannerFactory(const ScanResultMetadata* metadata, const AbstractScanCondition* joinCondition)
			: AbstractJoinScannerFactory(metadata, joinCondition){

}

InnerJoinScannerFactory::~InnerJoinScannerFactory() {
}

IJoinLeftSource* InnerJoinScannerFactory::createScannerAsLeftSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
	// FIXME createScannerAsLeftSource
	return nullptr;
}

IJoinRightSource* InnerJoinScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner, const ScanJoinContext* joinContext) {
	return nullptr;
}

} /* namespace codablecash */
