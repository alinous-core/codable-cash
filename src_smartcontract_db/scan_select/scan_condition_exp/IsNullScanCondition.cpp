/*
 * IsNullScanCondition.cpp
 *
 *  Created on: 2020/08/04
 *      Author: iizuka
 */

#include "scan_select/scan_condition_exp/IsNullScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_condition/IValueProvider.h"

#include "scan_select/scan_planner_scanner_ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner_scanner_ctx/FilterConditionStackMarker.h"

namespace codablecash {

IsNullScanCondition::IsNullScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_IS_NULL) {
	this->cond = nullptr;
	this->str = nullptr;
	this->notnull = false;
}

IsNullScanCondition::~IsNullScanCondition() {
	delete this->cond;
	resetStr();
}

void IsNullScanCondition::setCondition(IValueProvider* cond) noexcept {
	this->cond = cond;
	resetStr();
}

void IsNullScanCondition::setIsNull(bool notnull) noexcept {
	this->notnull = notnull;
}

const UnicodeString* IsNullScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		AbstractScanConditionElement* element = dynamic_cast<AbstractScanConditionElement*>(this->cond);
		this->str->append(element->toStringCode());

		this->str->append(L" IS");

		if(this->notnull){
			this->str->append(L" NOT");
		}

		this->str->append(L" NULL");
	}

	return this->str;
}

AbstractScanCondition* IsNullScanCondition::cloneCondition() const noexcept {
	IsNullScanCondition* cond = new IsNullScanCondition();

	cond->setCondition(this->cond->clone());
	cond->setIsNull(this->notnull);

	return cond;
}

void IsNullScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	FilterConditionStackMarker marker(detector->getStack());

	if(this->cond->isFilterable(vm, planner, detector)){
		detector->push(cloneCondition());
	}
}

void IsNullScanCondition::detectIndexCondition(VirtualMachine* vm,
		SelectScanPlanner* planner, TableIndexDetector* detector) {
	// FIXME detectIndexCondition
}

void IsNullScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void IsNullScanCondition::analyzeConditions(VirtualMachine* vm,	SelectScanPlanner* planner) {
	this->cond->analyzeConditions(vm, planner);
}


} /* namespace codablecash */
