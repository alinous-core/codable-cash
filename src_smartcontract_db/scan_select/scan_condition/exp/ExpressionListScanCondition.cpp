/*
 * ExpressionListScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_select/scan_condition/exp/ExpressionListScanCondition.h"

#include "engine/sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_condition/base/IValueProvider.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner/scanner/ctx/FilterConditionStackMarker.h"

namespace codablecash {

ExpressionListScanCondition::ExpressionListScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_EXP_LIST) {
	this->str = nullptr;
}

ExpressionListScanCondition::~ExpressionListScanCondition() {
	this->list.deleteElements();
	resetStr();
}

void ExpressionListScanCondition::addElement(IValueProvider* val) noexcept {
	this->list.addElement(val);
	resetStr();
}

const UnicodeString* ExpressionListScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			IValueProvider* vp = this->list.get(i);
			AbstractScanConditionElement* el = dynamic_cast<AbstractScanConditionElement*>(vp);

			if(i > 0){
				this->str->append(L", ");
			}

			this->str->append(el->toStringCode());
		}
	}

	return this->str;
}

AbstractScanCondition* ExpressionListScanCondition::cloneCondition() const noexcept {
	ExpressionListScanCondition* cond = new ExpressionListScanCondition();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* vp = this->list.get(i);

		cond->addElement(vp->clone());
	}

	return cond;
}

void ExpressionListScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	FilterConditionStackMarker marker(detector->getStack());

	if(isFilterable(vm, planner, detector)){
		detector->push(cloneCondition());
	}
}

void codablecash::ExpressionListScanCondition::detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner,
		TableIndexDetector* detector) {
	// FIXME detectIndexCondition
}


bool ExpressionListScanCondition::isFilterable(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) const noexcept {
	bool result = true;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* vp = this->list.get(i);

		if(!vp->isFilterable(vm, planner, detector)){
			result = false;
			break;
		}
	}

	return result;
}

void ExpressionListScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void ExpressionListScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* vp = this->list.get(i);

		vp->analyzeConditions(vm, planner);
	}
}


} /* namespace codablecash */
