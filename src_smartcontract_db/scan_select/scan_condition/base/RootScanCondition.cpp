/*
 * RootScanCondition.cpp
 *
 *  Created on: 2020/06/14
 *      Author: iizuka
 */

#include "scan_select/scan_condition/base/RootScanCondition.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionStackMarker.h"
#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"

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
	FilterConditionStackMarker marker(detector->getStack());

	if(this->cond != nullptr){
		this->cond->detectFilterConditions(vm, planner, detector);
	}
}

void codablecash::RootScanCondition::detectIndexCondition(VirtualMachine* vm,
		SelectScanPlanner* planner, TableIndexDetector* detector) {
}

AbstractScanCondition* RootScanCondition::cloneCondition() const noexcept {
	RootScanCondition* cond = new RootScanCondition();

	cond->addCondition(this->cond->cloneCondition());

	return cond;
}

} /* namespace codablecash */
