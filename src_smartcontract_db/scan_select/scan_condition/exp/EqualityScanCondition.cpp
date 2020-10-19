/*
 * EqualityScanCondition.cpp
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#include "scan_select/scan_condition/exp/EqualityScanCondition.h"

#include "engine/sc/CodeElement.h"

#include "scan_select/scan_condition/base/IValueProvider.h"

#include "engine/CdbException.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "scan_select/scan_planner/scanner/join/JoinCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidateHolder.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidateStackMarker.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner/scanner/ctx/FilterConditionStackMarker.h"

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
	FilterConditionStackMarker marker(detector->getStack());

	if(this->left->isFilterable(vm, planner, detector) &&
			this->right->isFilterable(vm, planner, detector)){
		detector->push(cloneCondition());
	}
}

void EqualityScanCondition::detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner,
		TableIndexDetector* detector) {
	// FIXME detectIndexCondition
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

	const AbstractScanTableTarget* left = jholder->getLeft();
	const AbstractScanTableTarget* right = jholder->getRight();
	if(!hasLeftAndRightScanTarget(left, right)){
		return;
	}

	JoinCandidateStackMarker marker(jholder->getStack());

	JoinCandidate* candidate = new JoinCandidate(joinType, dynamic_cast<ColumnIdentifierScanParam*>(this->left)
				, dynamic_cast<ColumnIdentifierScanParam*>(this->right));
	StackRelease<JoinCandidate> st_candidate(candidate);

	if(jholder->isJoinCondition(candidate)){
		jholder->push(st_candidate.move());
	}
}

bool EqualityScanCondition::hasLeftAndRightScanTarget(
		const AbstractScanTableTarget* left,
		const AbstractScanTableTarget* right) const noexcept {
	bool l = false;
	bool r = false;

	ColumnIdentifierScanParam* lparam = dynamic_cast<ColumnIdentifierScanParam*>(this->left);
	ColumnIdentifierScanParam* rparam = dynamic_cast<ColumnIdentifierScanParam*>(this->right);

	if(lparam->getTarget() == left){
		l = true;
	}else if(lparam->getTarget() == right){
		r = true;
	}

	if(rparam->getTarget() == left){
		l = true;
	}else if(rparam->getTarget() == right){
		r = true;
	}

	return l && r;
}

} /* namespace codablecash */
