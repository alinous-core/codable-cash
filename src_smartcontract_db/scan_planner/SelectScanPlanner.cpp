/*
 * SelectScanPlanner.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "scan_planner/SelectScanPlanner.h"

#include "scan_planner/ConditionsHolder.h"
#include <cassert>

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

SelectScanPlanner::SelectScanPlanner() {
	this->conditions = new ConditionsHolder();

}

SelectScanPlanner::~SelectScanPlanner() {
	delete this->conditions;
}

void SelectScanPlanner::processExpression(AbstractScanCondition* cond) {
	this->conditions->processExpression(cond);
}

void SelectScanPlanner::pushParam(AbstractScanConditionElement* param) noexcept {
	this->conditions->pushParam(param);
}

AbstractScanConditionElement* SelectScanPlanner::popParam() noexcept {
	return this->conditions->popParam();
}

} /* namespace codablecash */
