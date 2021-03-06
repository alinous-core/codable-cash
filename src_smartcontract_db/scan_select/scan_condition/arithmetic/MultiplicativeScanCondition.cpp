/*
 * MultiplicativeScanCondition.cpp
 *
 *  Created on: 2020/08/04
 *      Author: iizuka
 */

#include "scan_select/scan_condition/arithmetic/MultiplicativeScanCondition.h"

#include "engine/sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "lang_sql/sql_expression/SqlMultiplicativeExpression.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner/scanner/ctx/FilterConditionStackMarker.h"

namespace codablecash {

MultiplicativeScanCondition::MultiplicativeScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_MULTIPLICATIVE), operations(2){
	this->str = nullptr;
}

MultiplicativeScanCondition::~MultiplicativeScanCondition() {
	this->list.deleteElements();
	resetStr();
}

const UnicodeString* MultiplicativeScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			if(i > 0){
				int pos = i - 1;
				uint8_t op = this->operations.get(pos);

				if(op == SqlMultiplicativeExpression::MUL){
					this->str->append(L" * ");
				}
				else if(op == SqlMultiplicativeExpression::DIV){
					this->str->append(L" / ");
				}
				else if(op == SqlMultiplicativeExpression::MOD){
					this->str->append(L" % ");
				}
			}

			IValueProvider* vp = this->list.get(i);
			AbstractScanConditionElement* el = dynamic_cast<AbstractScanConditionElement*>(vp);

			this->str->append(el->toStringCode());
		}

	}

	return this->str;
}

void MultiplicativeScanCondition::addOperand(IValueProvider* vp) noexcept {
	this->list.addElement(vp);
	resetStr();
}

void MultiplicativeScanCondition::addOperator(uint8_t op) noexcept {
	this->operations.addElement(op);
	resetStr();
}

void MultiplicativeScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	if(isFilterable(vm, planner, detector)){
		detector->push(cloneCondition());
	}
}

void MultiplicativeScanCondition::detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner,
		TableIndexDetector* detector) {
}

void MultiplicativeScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void MultiplicativeScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* vp = this->list.get(i);

		vp->analyzeConditions(vm, planner);
	}
}

bool MultiplicativeScanCondition::isFilterable(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) const noexcept {
	FilterConditionStackMarker marker(detector->getStack());

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

IValueProvider* MultiplicativeScanCondition::clone() const noexcept {
	MultiplicativeScanCondition* cond = new MultiplicativeScanCondition();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* vp = this->list.get(i);

		cond->addOperand(vp->clone());
	}

	maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);

		cond->addOperator(op);
	}

	return cond;
}

AbstractScanCondition* MultiplicativeScanCondition::cloneCondition() const noexcept {
	return dynamic_cast<MultiplicativeScanCondition*>(clone());
}

} /* namespace codablecash */
