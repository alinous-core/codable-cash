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
	push(this->root);
}

ConditionsHolder::~ConditionsHolder() {
	delete this->root;
	this->paramStack.deleteElements();
}

void ConditionsHolder::processExpression(AbstractScanCondition* cond) {
	AbstractScanCondition* parentCond = top();
	parentCond->addCondition(cond);

	push(cond);
}


void ConditionsHolder::push(AbstractScanCondition* cond) noexcept {
	this->stack.addElement(cond);
}

AbstractScanCondition* ConditionsHolder::top() const noexcept {
	int index = this->stack.size() - 1;
	return this->stack.get(index);
}

void ConditionsHolder::pop() noexcept {
	int index = this->stack.size() - 1;
	this->stack.remove(index);
}

void ConditionsHolder::pushParam(AbstractScanConditionParameter* param) noexcept {
	this->paramStack.addElement(param);
}

AbstractScanConditionParameter* ConditionsHolder::topParam() const noexcept {
	int index = this->paramStack.size() - 1;
	return this->paramStack.get(index);
}

AbstractScanConditionParameter* ConditionsHolder::popParam() noexcept {
	int index = this->paramStack.size() - 1;
	AbstractScanConditionParameter* ret = topParam();

	this->paramStack.remove(index);

	return ret;
}

} /* namespace codablecash */
