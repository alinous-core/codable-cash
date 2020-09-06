/*
 * RootScanCondition.cpp
 *
 *  Created on: 2020/06/14
 *      Author: iizuka
 */

#include "scan_condition/RootScanCondition.h"

namespace codablecash {

RootScanCondition::RootScanCondition() : AbstractScanCondition(0) {
	this->cond = nullptr;
}

RootScanCondition::~RootScanCondition() {
	delete this->cond;
}

void RootScanCondition::addCondition(AbstractScanCondition* cond) {
	delete this->cond;
	this->cond = cond;
}

const UnicodeString* RootScanCondition::toStringCode() noexcept {
	return this->cond->toStringCode();
}

void RootScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	if(this->cond != nullptr){
		this->cond->analyzeConditions(vm, planner);
	}
}

void RootScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	if(this->cond != nullptr){
		this->cond->detectFilterConditions(vm, planner, detector);
	}
}

AbstractScanCondition* RootScanCondition::cloneCondition() const noexcept {
	RootScanCondition* cond = new RootScanCondition();

	cond->addCondition(this->cond->cloneCondition());

	return cond;
}

} /* namespace codablecash */
