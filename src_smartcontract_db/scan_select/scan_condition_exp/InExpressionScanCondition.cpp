/*
 * InExpressionScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_select/scan_condition_exp/InExpressionScanCondition.h"

#include "engine/sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_condition/IValueProvider.h"

#include "scan_select/scan_condition_exp/ExpressionListScanCondition.h"

#include "scan_select/scan_planner_scanner_ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner_scanner_ctx/FilterConditionStackMarker.h"

namespace codablecash {

InExpressionScanCondition::InExpressionScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_IN) {
	this->left = nullptr;
	this->list = nullptr;

	this->str = nullptr;
}

InExpressionScanCondition::~InExpressionScanCondition() {
	delete this->left;
	delete this->list;
	resetStr();
}

void InExpressionScanCondition::setLeft(IValueProvider* cond) noexcept {
	this->left = cond;
	resetStr();
}

void InExpressionScanCondition::setList(ExpressionListScanCondition* list) noexcept {
	this->list = list;
	resetStr();
}

const UnicodeString* InExpressionScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		AbstractScanConditionElement* el = dynamic_cast<AbstractScanConditionElement*>(left);
		this->str->append(el->toStringCode());
		this->str->append(L" IN (");

		this->str->append(this->list->toStringCode());
		this->str->append(L")");
	}

	return this->str;
}

AbstractScanCondition* InExpressionScanCondition::cloneCondition() const noexcept {
	InExpressionScanCondition* cond = new InExpressionScanCondition();

	cond->setLeft(this->left->clone());
	cond->setList(dynamic_cast<ExpressionListScanCondition*>(this->list->cloneCondition()));

	return cond;
}

void InExpressionScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	FilterConditionStackMarker marker(detector->getStack());

	bool leftFilterable = this->left->isFilterable(vm, planner, detector);

	if(leftFilterable){
		this->list->detectFilterConditions(vm, planner, detector);
		if(!detector->isEmpty()){
			delete detector->pop();

			detector->push(cloneCondition());
		}
	}
}

void InExpressionScanCondition::detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner,
		TableIndexDetector* detector) {
	// FIXME detectIndexCondition
}


void InExpressionScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void InExpressionScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->analyzeConditions(vm, planner);
}


} /* namespace codablecash */
