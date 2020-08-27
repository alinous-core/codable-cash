/*
 * AbstractJoinScanTarget.cpp
 *
 *  Created on: 2020/08/09
 *      Author: iizuka
 */

#include "scan_table/AbstractJoinScanTarget.h"

#include "base/UnicodeString.h"

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

AbstractJoinScanTarget::AbstractJoinScanTarget() {
	this->left = nullptr;
	this->right = nullptr;
	this->cond = nullptr;

	this->str = nullptr;
}

AbstractJoinScanTarget::~AbstractJoinScanTarget() {
	delete this->left;
	delete this->right;
	delete this->cond;

	resetStr();
}

void AbstractJoinScanTarget::setLeft(AbstractScanTableTarget* left) noexcept {
	this->left = left;
	resetStr();
}

void AbstractJoinScanTarget::setRight(AbstractScanTableTarget* right) noexcept {
	this->right = right;
	resetStr();
}

void AbstractJoinScanTarget::setCondition(AbstractScanCondition* cond) noexcept {
	this->cond = cond;
	resetStr();
}

void AbstractJoinScanTarget::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void AbstractJoinScanTarget::addConditionString() noexcept {
	if(this->cond != nullptr){
		this->str->append(L" ON ");
		this->str->append(this->cond->toStringCode());
	}
}

void AbstractJoinScanTarget::resolveTable(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->resolveTable(vm, planner);
	this->right->resolveTable(vm, planner);
}


} /* namespace codablecash */
