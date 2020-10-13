/*
 * ParenthesisScanCondition.cpp
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#include "scan_select/scan_condition_exp/ParenthesisScanCondition.h"

#include "engine/sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_planner_scanner_ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner_scanner_ctx/FilterConditionStackMarker.h"

using namespace alinous;

namespace codablecash {

ParenthesisScanCondition::ParenthesisScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_NOT) {
	this->cond = nullptr;
	this->str = nullptr;
}

ParenthesisScanCondition::~ParenthesisScanCondition() {
	delete this->cond;
	resetStr();
}

void ParenthesisScanCondition::addCondition(AbstractScanCondition* cond) {
	delete this->cond;
	this->cond = cond;
}

const UnicodeString* ParenthesisScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"(");

		this->str->append(this->cond->toStringCode());

		this->str->append(L")");
	}

	return this->str;
}

void ParenthesisScanCondition::collectJoinCandidate(VirtualMachine* vm,
		SelectScanPlanner* planner, int joinType,
		JoinCandidateHolder* jholder) {
	this->cond->collectJoinCandidate(vm, planner, joinType, jholder);
}

AbstractScanCondition* ParenthesisScanCondition::cloneCondition() const noexcept {
	ParenthesisScanCondition* cond = new ParenthesisScanCondition();

	cond->addCondition(this->cond->cloneCondition());

	return cond;
}

void ParenthesisScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	FilterConditionStackMarker marker(detector->getStack());

	this->cond->detectFilterConditions(vm, planner, detector);

	if(!detector->isEmpty()){
		AbstractScanCondition* inner = detector->pop();

		ParenthesisScanCondition* newP = new ParenthesisScanCondition();
		newP->addCondition(inner);

		detector->push(newP);
	}
}

void ParenthesisScanCondition::detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner,
		TableIndexDetector* detector) {
	this->cond->detectIndexCondition(vm, planner, detector);
}


void ParenthesisScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void ParenthesisScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->cond->analyzeConditions(vm, planner);
}


} /* namespace codablecash */
