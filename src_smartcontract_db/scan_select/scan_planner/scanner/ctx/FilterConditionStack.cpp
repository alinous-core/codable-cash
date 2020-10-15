/*
 * FilterConditionStack.cpp
 *
 *  Created on: 2020/09/06
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/ctx/FilterConditionStack.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

namespace codablecash {

FilterConditionStack::FilterConditionStack() : markStack(4) {

}

FilterConditionStack::~FilterConditionStack() {
	this->stack.deleteElements();
}

bool FilterConditionStack::isEmpty() const noexcept {
	if(this->markStack.size() == 0){
		return this->stack.isEmpty();
	}

	int topidx = this->markStack.size() - 1;
	int index = this->markStack.get(topidx);

	return this->stack.size() == index;
}

void FilterConditionStack::push(AbstractScanCondition* cond) noexcept {
	this->stack.addElement(cond);
}

AbstractScanCondition* FilterConditionStack::pop() noexcept {
	int index = this->stack.size() - 1;
	return this->stack.remove(index);
}

void FilterConditionStack::mark() noexcept {
	int index = this->stack.size();
	this->markStack.addElement(index);
}

void FilterConditionStack::unmark() noexcept {
	int index = this->markStack.size() - 1;
	this->markStack.remove(index);
}

} /* namespace codablecash */
