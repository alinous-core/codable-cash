/*
 * TableScannerFactory.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/factory/TableScannerFactory.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

namespace codablecash {

TableScannerFactory::TableScannerFactory(const ScanResultMetadata* metadata, const AbstractIndexCandidate* indexCandidate)
				: AbstractScannerFactory(metadata){
	this->indexCandidate = indexCandidate != nullptr ? indexCandidate->copy() : nullptr;
}

TableScannerFactory::~TableScannerFactory() {
	delete this->indexCandidate;
}

IJoinLeftSource* TableScannerFactory::createScannerAsLeftSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
	// TODO left source
}

IJoinRightSource* TableScannerFactory::createScannerAsRightSource(
		VirtualMachine* vm, SelectScanPlanner* planner) {
	// TODO right source
}

} /* namespace codablecash */
