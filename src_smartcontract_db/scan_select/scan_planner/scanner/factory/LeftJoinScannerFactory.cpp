/*
 * LeftJoinScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/LeftJoinScannerFactory.h"

#include "trx/scan/transaction_scanner_join/OuterJoinExecutor.h"

namespace codablecash {

LeftJoinScannerFactory::LeftJoinScannerFactory(const ScanResultMetadata* metadata)
				: AbstractJoinScannerFactory(metadata){

}

LeftJoinScannerFactory::~LeftJoinScannerFactory() {

}

IJoinLeftSource* LeftJoinScannerFactory::createScannerAsLeftSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {

	OuterJoinExecutor* exec = nullptr;

	// TODO createScannerAsLeftSource
	return exec;
}

IJoinRightSource* LeftJoinScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
	return nullptr;
}


} /* namespace codablecash */
