/*
 * FilterConditionDitector.cpp
 *
 *  Created on: 2020/09/02
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx/FilterConditionDitector.h"

namespace codablecash {

FilterConditionDitector::FilterConditionDitector(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->vm = vm;
	this->planner = planner;
}

FilterConditionDitector::~FilterConditionDitector() {
	this->vm = nullptr;
	this->planner = nullptr;
}

} /* namespace codablecash */
