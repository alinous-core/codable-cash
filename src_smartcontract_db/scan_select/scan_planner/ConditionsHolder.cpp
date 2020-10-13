/*
 * ConditionsHolder.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "scan_select/scan_planner/ConditionsHolder.h"
#include "scan_select/scan_planner/ConditionsHolderStack.h"

#include "scan_select/scan_condition/RootScanCondition.h"

#include "lang_sql/sql/AbstractSQLExpression.h"

#include "scan_select/scan_condition/params/AbstractScanConditionParameter.h"


namespace codablecash {

ConditionsHolder::ConditionsHolder() {
	this->root = new RootScanCondition();
	this->stack = new ConditionsHolderStack();
}

ConditionsHolder::~ConditionsHolder() {
	delete this->stack;
	delete this->root;
}

void ConditionsHolder::push(AbstractScanConditionElement* cond) noexcept {
	this->stack->push(cond);
}

AbstractScanConditionElement* ConditionsHolder::top() const noexcept {
	int index = this->stack->size() - 1;
	return this->stack->get(index);
}

AbstractScanConditionElement* ConditionsHolder::pop() noexcept {
	return this->stack->pop();
}

RootScanCondition* ConditionsHolder::getRoot() const noexcept {
	return this->root;
}

void ConditionsHolder::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->root->analyzeConditions(vm, planner);
}

} /* namespace codablecash */
