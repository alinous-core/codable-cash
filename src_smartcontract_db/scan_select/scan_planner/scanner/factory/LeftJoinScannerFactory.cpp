/*
 * LeftJoinScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/LeftJoinScannerFactory.h"

#include "trx/scan/transaction_scanner_join/OuterJoinExecutor.h"
#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"
#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

#include "scan_select/scan_planner/scanner/ctx/ScanJoinContext.h"

namespace codablecash {

LeftJoinScannerFactory::LeftJoinScannerFactory(const ScanResultMetadata* metadata)
				: AbstractJoinScannerFactory(metadata){

}

LeftJoinScannerFactory::~LeftJoinScannerFactory() {

}

IJoinLeftSource* LeftJoinScannerFactory::createScannerAsLeftSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {

	IJoinLeftSource* leftSource = this->leftFactory->createScannerAsLeftSource(vm, planner);
	IJoinRightSource* rightSource = this->rightFactory->createScannerAsRightSource(vm, planner);


	ScanJoinContext* joinContext = new ScanJoinContext(this->joinCandidate);
	OuterJoinExecutor* exec = new OuterJoinExecutor(leftSource, rightSource, this->metadata, joinContext);

	// TODO createScannerAsLeftSource
	return exec;
}

IJoinRightSource* LeftJoinScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
	return nullptr;
}


} /* namespace codablecash */
