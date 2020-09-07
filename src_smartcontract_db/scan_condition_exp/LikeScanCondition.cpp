/*
 * LikeScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_exp/LikeScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_condition/IValueProvider.h"

#include "scan_planner_scanner_ctx/FilterConditionDitector.h"
#include "scan_planner_scanner_ctx/FilterConditionStackMarker.h"

using namespace alinous;

namespace codablecash {

LikeScanCondition::LikeScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_LIKE) {
	this->left = nullptr;
	this->right = nullptr;
	this->escape = nullptr;

	this->str = nullptr;
}

LikeScanCondition::~LikeScanCondition() {
	delete this->left;
	delete this->right;
	delete this->escape;

	resetStr();
}

void LikeScanCondition::setLeft(IValueProvider* left) noexcept {
	this->left = left;
}

void LikeScanCondition::setRight(IValueProvider* right) noexcept {
	this->right = right;
}

void LikeScanCondition::setEscape(IValueProvider* escape) noexcept {
	this->escape = escape;
}


const UnicodeString* LikeScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"");

		AbstractScanConditionElement* cond = dynamic_cast<AbstractScanConditionElement*>(this->left);
		this->str->append(cond->toStringCode());

		this->str->append(L" LIKE ");

		cond = dynamic_cast<AbstractScanConditionElement*>(this->right);
		this->str->append(cond->toStringCode());

		if(this->escape != nullptr){
			this->str->append(L" ESCAPE ");
			cond = dynamic_cast<AbstractScanConditionElement*>(this->escape);
			this->str->append(cond->toStringCode());
		}
	}

	return this->str;
}

AbstractScanCondition* LikeScanCondition::cloneCondition() const noexcept {
	LikeScanCondition* cond = new LikeScanCondition();

	cond->setLeft(this->left->clone());
	cond->setRight(this->right->clone());

	if(this->escape != nullptr){
		cond->setEscape(this->escape->clone());
	}

	return cond;
}

void LikeScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	FilterConditionStackMarker marker(detector->getStack());

	if(this->left->isFilterable(vm, planner, detector) &&
			this->right->isFilterable(vm, planner, detector) &&
			(this->escape == nullptr || this->escape->isFilterable(vm, planner, detector))){
		detector->push(cloneCondition());
	}
}

void LikeScanCondition::detectIndexCondition(VirtualMachine* vm,
		SelectScanPlanner* planner, TableIndexDetector* detector) {
}

void LikeScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void LikeScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->analyzeConditions(vm, planner);
	this->right->analyzeConditions(vm, planner);

	if(this->escape != nullptr){
		this->escape->analyzeConditions(vm, planner);
	}
}


} /* namespace codablecash */
