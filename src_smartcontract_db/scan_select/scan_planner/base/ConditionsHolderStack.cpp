/*
 * ConditionsHolderStack.cpp
 *
 *  Created on: 2020/09/06
 *      Author: iizuka
 */

#include "scan_select/scan_planner/base/ConditionsHolderStack.h"

#include "scan_select/scan_condition/base/AbstractScanConditionElement.h"

namespace codablecash {

ConditionsHolderStack::ConditionsHolderStack() : markStack(4) {

}

ConditionsHolderStack::~ConditionsHolderStack() {
	this->stack.deleteElements();
}

bool ConditionsHolderStack::isEmpty() const noexcept {
	if(this->markStack.size() == 0){
		return this->stack.isEmpty();
	}

	int topidx = this->markStack.size() - 1;
	int index = this->markStack.get(topidx);

	return this->stack.size() == index;
}

void ConditionsHolderStack::push(AbstractScanConditionElement* candidate) noexcept {
	this->stack.addElement(candidate);
}

AbstractScanConditionElement* ConditionsHolderStack::pop() noexcept {
	int index = this->stack.size() - 1;
	return this->stack.remove(index);
}

int ConditionsHolderStack::size() const noexcept {
	return this->stack.size();
}

AbstractScanConditionElement* codablecash::ConditionsHolderStack::get(int index) const noexcept {
	return this->stack.get(index);
}

void ConditionsHolderStack::mark() noexcept {
	int index = this->stack.size();
	this->markStack.addElement(index);
}

void ConditionsHolderStack::unmark() noexcept {
	int index = this->markStack.size() - 1;
	this->markStack.remove(index);
}

} /* namespace codablecash */
