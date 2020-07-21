/*
 * ConditionStackPopper.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_planner/ConditionStackPopper.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionsHolder.h"

namespace codablecash {

ConditionStackPopper::ConditionStackPopper(SelectScanPlanner* planner) {
	this->conditions = planner->getConditions();
}

ConditionStackPopper::~ConditionStackPopper() {
	this->conditions->pop();
}

} /* namespace codablecash */
