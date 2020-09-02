/*
 * EqualityScanCondition.cpp
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#include "scan_condition_exp/EqualityScanCondition.h"

#include "sc/CodeElement.h"

#include "scan_condition/IValueProvider.h"

#include "engine/CdbException.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "scan_planner_scanner_ctx_join/JoinCandidate.h"
#include "scan_planner_scanner_ctx_join/JoinCandidateHolder.h"

#include "scan_condition_params/ColumnIdentifierScanParam.h"


using namespace alinous;

namespace codablecash {

EqualityScanCondition::EqualityScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_EQUALITY) {
	this->left = nullptr;
	this->right = nullptr;
	this->str = nullptr;
}

EqualityScanCondition::~EqualityScanCondition() {
	delete this->left;
	delete this->right;
	resetStr();
}

void EqualityScanCondition::setLeft(IValueProvider* element) {
	this->left = element;
	resetStr();
}

void EqualityScanCondition::setRight(IValueProvider* element) {
	this->right = element;
	resetStr();
}

const UnicodeString* EqualityScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"");

		AbstractScanConditionElement* cond = dynamic_cast<AbstractScanConditionElement*>(this->left);
		this->str->append(cond->toStringCode());

		this->str->append(L" = ");

		cond = dynamic_cast<AbstractScanConditionElement*>(this->right);
		this->str->append(cond->toStringCode());
	}

	return this->str;
}

AbstractScanCondition* EqualityScanCondition::cloneCondition() const noexcept {
	EqualityScanCondition* cond = new EqualityScanCondition();

	cond->setLeft(this->left->clone());
	cond->setRight(this->right->clone());

	return cond;
}

void EqualityScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	if(this->left->isFilterable(vm, planner, detector) &&
			this->right->isFilterable(vm, planner, detector)){
		detector->push(cloneCondition());
	}
}

void EqualityScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void EqualityScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->analyzeConditions(vm, planner);
	this->right->analyzeConditions(vm, planner);
}

void EqualityScanCondition::collectJoinCandidate(VirtualMachine* vm, SelectScanPlanner* planner, int joinType,
							JoinCandidateHolder* jholder) {
	if(!(this->left->isColumn() && this->right->isColumn())){
		return;
	}

	JoinCandidate* candidate = new JoinCandidate(joinType, dynamic_cast<ColumnIdentifierScanParam*>(this->left)
				, dynamic_cast<ColumnIdentifierScanParam*>(this->right));
	StackRelease<JoinCandidate> st_candidate(candidate);

	if(jholder->isJoinCondition(candidate)){
		jholder->push(st_candidate.move());
	}
}

} /* namespace codablecash */
