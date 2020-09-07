/*
 * TableIndexDetector.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_index/TableIndexDetector.h"

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

TableIndexDetector::TableIndexDetector(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->vm = vm;
	this->planner = planner;
}

TableIndexDetector::~TableIndexDetector() {
	this->vm = nullptr;
	this->planner = nullptr;
}

void TableIndexDetector::detect(AbstractScanCondition* cond) {

}

} /* namespace codablecash */
