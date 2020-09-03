/*
 * AndScanCondition.cpp
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#include "scan_condition_logical/AndScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_planner_scanner_ctx/FilterConditionDitector.h"

#include "scan_condition/AbstractScanCondition.h"

#include "scan_planner_scanner_ctx_join/JoinCandidateStackMarker.h"
#include "scan_planner_scanner_ctx_join/JoinCandidateHolder.h"

using namespace alinous;

namespace codablecash {

AndScanCondition::AndScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_AND) {
	this->str = nullptr;
}

AndScanCondition::~AndScanCondition() {
	this->list.deleteElements();
	resetStr();
}

void AndScanCondition::addCondition(AbstractScanCondition* cond) {
	this->list.addElement(cond);
	resetStr();
}

const UnicodeString* AndScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanCondition* cond = this->list.get(i);

			if(i != 0){
				this->str->append(L" AND ");
			}

			this->str->append(cond->toStringCode());
		}
	}

	return this->str;
}

AbstractScanCondition* AndScanCondition::cloneCondition() const noexcept {
	AndScanCondition* cond = new AndScanCondition();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cnd = this->list.get(i);

		cond->addCondition(cnd->cloneCondition());
	}

	return cond;
}

void AndScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	ArrayList<AbstractScanCondition> scanList;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cnd = this->list.get(i);

		cnd->detectFilterConditions(vm, planner, detector);
		if(!detector->isEmpty()){
			scanList.addElement(detector->pop());
		}
	}

	maxLoop = scanList.size();
	if(maxLoop > 1){
		AndScanCondition* newAnd = new AndScanCondition();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanCondition* cnd = scanList.get(i);

			newAnd->addCondition(cnd);
		}

		detector->push(newAnd);
	}
	else if(maxLoop == 1){
		detector->push(scanList.get(0));
	}
}

void AndScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void AndScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cond = this->list.get(i);

		cond->analyzeConditions(vm, planner);
	}
}

void AndScanCondition::collectJoinCandidate(VirtualMachine* vm,
		SelectScanPlanner* planner, int joinType,
		JoinCandidateHolder* jholder) {

	JoinCandidateStackMarker marker(jholder->getStack());

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cond = this->list.get(i);


	}
	// FIXME collectJoinCandidate
}


} /* namespace codablecash */
