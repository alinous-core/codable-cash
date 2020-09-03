/*
 * OrScanCondition.cpp
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#include "scan_condition_logical/OrScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_planner_scanner_ctx/FilterConditionDitector.h"

#include "scan_planner_scanner_ctx_join/JoinCandidateStackMarker.h"
#include "scan_planner_scanner_ctx_join/JoinCandidateHolder.h"

using namespace alinous;

namespace codablecash {

OrScanCondition::OrScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_OR) {
	this->str = nullptr;
}

OrScanCondition::~OrScanCondition() {
	this->list.deleteElements();
	resetStr();
}

void OrScanCondition::addCondition(AbstractScanCondition* cond) {
	this->list.addElement(cond);
	resetStr();
}

const UnicodeString* OrScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanCondition* cond = this->list.get(i);

			if(i != 0){
				this->str->append(L" OR ");
			}

			this->str->append(cond->toStringCode());
		}
	}

	return this->str;
}

AbstractScanCondition* OrScanCondition::cloneCondition() const noexcept {
	OrScanCondition* cond = new OrScanCondition();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cnd = this->list.get(i);

		cond->addCondition(cnd->cloneCondition());
	}

	return cond;
}

void OrScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	bool allavailable = true;
	ArrayList<AbstractScanCondition> scanList;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cond = this->list.get(i);

		cond->detectFilterConditions(vm, planner, detector);
		if(detector->isEmpty()){
			allavailable = false;
			break;
		}

		scanList.addElement(detector->pop());
	}

	if(!allavailable){
		scanList.deleteElements();
		return;
	}

	OrScanCondition* newOr = new OrScanCondition();

	maxLoop = scanList.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cond = scanList.get(i);

		newOr->addCondition(cond);
	}
}

void OrScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void OrScanCondition::analyzeConditions(VirtualMachine* vm,	SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cond = this->list.get(i);

		cond->analyzeConditions(vm, planner);
	}
}

void OrScanCondition::collectJoinCandidate(VirtualMachine* vm,
		SelectScanPlanner* planner, int joinType, JoinCandidateHolder* jholder) {

	JoinCandidateStackMarker marker(jholder->getStack());


	// FIXME
}

} /* namespace codablecash */
