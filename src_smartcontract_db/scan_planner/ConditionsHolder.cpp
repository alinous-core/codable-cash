/*
 * ConditionsHolder.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "scan_planner/ConditionsHolder.h"

#include "scan_condition/RootScanCondition.h"

#include "sql/AbstractSQLExpression.h"

#include "scan_condition_params/AbstractScanConditionParameter.h"

namespace codablecash {

ConditionsHolder::ConditionsHolder() {
	this->root = new RootScanCondition();
}

ConditionsHolder::~ConditionsHolder() {
	this->stack.deleteElements();
	delete this->root;
}

void ConditionsHolder::push(AbstractScanConditionElement* cond) noexcept {
	this->stack.addElement(cond);
}

AbstractScanConditionElement* ConditionsHolder::top() const noexcept {
	int index = this->stack.size() - 1;
	return this->stack.get(index);
}

AbstractScanConditionElement* ConditionsHolder::pop() noexcept {
	int index = this->stack.size() - 1;
	return this->stack.remove(index);
}

RootScanCondition* ConditionsHolder::getRoot() const noexcept {
	return this->root;
}

} /* namespace codablecash */
