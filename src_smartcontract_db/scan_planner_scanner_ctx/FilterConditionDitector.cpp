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
	this->stack.deleteElements();

	this->vm = nullptr;
	this->planner = nullptr;
}

void FilterConditionDitector::detect(AbstractScanTableTarget* target) {
	ConditionsHolder* holder = planner->getConditions();

	target->collectScanTargets(this->vm, this->planner, &this->list);

	RootScanCondition* root = holder->getRoot();

}

bool FilterConditionDitector::hasTarget(AbstractScanTableTarget* target) const noexcept {
	bool result = false;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanTableTarget* t = this->list.get(i);

		if(t == target){
			result = true;
			break;
		}
	}

	return result;
}

bool FilterConditionDitector::isEmpty() const noexcept {
	return this->stack.isEmpty();
}

void FilterConditionDitector::push(AbstractScanCondition* cond) noexcept {
	this->stack.addElement(cond);
}

AbstractScanCondition* FilterConditionDitector::pop() noexcept {
	int index = this->stack.size() - 1;
	return this->stack.remove(index);
}

} /* namespace codablecash */
