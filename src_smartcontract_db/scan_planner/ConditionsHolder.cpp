/*
 * ConditionsHolder.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "scan_planner/ConditionsHolder.h"

#include "scan_condition/RootScanCondition.h"

#include "sql/AbstractSQLExpression.h"

namespace codablecash {

ConditionsHolder::ConditionsHolder() {
	this->root = new RootScanCondition();
	push(this->root);
}

ConditionsHolder::~ConditionsHolder() {
	delete this->root;
}

void ConditionsHolder::processExpression(AbstractScanCondition* cond) {
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


} /* namespace codablecash */
