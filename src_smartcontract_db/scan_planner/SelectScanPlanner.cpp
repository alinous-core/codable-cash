/*
 * SelectScanPlanner.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include <cassert>

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionsHolder.h"
#include "scan_planner/TablesHolder.h"

#include "scan_condition/AbstractScanCondition.h"


namespace codablecash {

SelectScanPlanner::SelectScanPlanner() {
	this->conditions = new ConditionsHolder();
	this->tablesHolder = new TablesHolder();
}

SelectScanPlanner::~SelectScanPlanner() {
	delete this->conditions;
	delete this->tablesHolder;
}

void SelectScanPlanner::push(AbstractScanConditionElement* cond) noexcept {
	this->conditions->push(cond);
}

AbstractScanConditionElement* SelectScanPlanner::top() const noexcept {
	return this->conditions->top();
}

AbstractScanConditionElement* SelectScanPlanner::pop() noexcept{
	return this->conditions->pop();
}

} /* namespace codablecash */
