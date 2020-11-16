/*
 * AndScanCondition.cpp
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#include "scan_select/scan_condition/logical/AndScanCondition.h"

#include "engine/sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner/scanner/ctx/FilterConditionStackMarker.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

#include "scan_select/scan_planner/scanner/join/JoinCandidateStackMarker.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidateHolder.h"
#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinMultipleCandidate.h"



#include "scan_select/scan_planner/scanner/index/TableIndexDetector.h"
#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/MultipleIndexCandidate.h"

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
	FilterConditionStackMarker marker(detector->getStack());

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

void AndScanCondition::detectIndexCondition(VirtualMachine* vm,	SelectScanPlanner* planner, TableIndexDetector* detector) {
	ArrayList<AbstractIndexCandidate> list;
	list.setDeleteOnExit();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cond = this->list.get(i);

		cond->detectIndexCondition(vm, planner, detector);

		if(!detector->isEmpty()){
			AbstractIndexCandidate* c = detector->pop();
			list.addElement(c);
		}
	}

	if(list.isEmpty()){
		return;
	}
	else if(list.size() == 1){
		AbstractIndexCandidate* c = list.get(0);
		detector->push(c);

		return;
	}

	// and
	//MultipleIndexCandidate* candidate = new MultipleIndexCandidate();

	AbstractIndexCandidate* candidate = list.get(0);

	maxLoop = list.size();
	for(int i = 1; i != maxLoop; ++i){
		const AbstractIndexCandidate* c = list.get(i);


	}

	detector->push(candidate);

	// TODO detectIndexCondition
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

	ArrayList<AbstractJoinCandidate> operandList;
	operandList.setDeleteOnExit();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanCondition* cond = this->list.get(i);

		cond->collectJoinCandidate(vm, planner, joinType, jholder);
		if(!jholder->isEmpty()){
			AbstractJoinCandidate* c = jholder->pop();

			operandList.addElement(c);
		}
	}

	int listSize = operandList.size();
	if(listSize > 0){
		if(listSize == 1){
			const AbstractJoinCandidate* c = operandList.get(0);
			jholder->push(c->copy());
		}
		else{
			AbstractJoinCandidate* multi = new JoinMultipleCandidate(joinType);

			for(int i = 0; i != listSize; ++i){
				AbstractJoinCandidate* c = operandList.get(i);

				AbstractJoinCandidate* newmulti = multi->multiply(c);

				delete multi;
				multi = newmulti;
			}

			jholder->push(multi);
		}

	}
}


} /* namespace codablecash */
