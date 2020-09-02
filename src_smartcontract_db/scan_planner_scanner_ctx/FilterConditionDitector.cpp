/*
 * FilterConditionDitector.cpp
 *
 *  Created on: 2020/09/02
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx/FilterConditionDitector.h"

#include "scan_table/AbstractScanTableTarget.h"

#include "scan_planner/ConditionsHolder.h"
#include "scan_planner/SelectScanPlanner.h"

#include "scan_condition/RootScanCondition.h"

namespace codablecash {

FilterConditionDitector::FilterConditionDitector(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->vm = vm;
	this->planner = planner;
}

FilterConditionDitector::~FilterConditionDitector() {
	this->vm = nullptr;
	this->planner = nullptr;
}

void FilterConditionDitector::detect(AbstractScanTableTarget* target) {
	ConditionsHolder* holder = planner->getConditions();

	target->collectScanTargets(this->vm, this->planner, &this->list);

	RootScanCondition* root = holder->getRoot();

}

} /* namespace codablecash */
