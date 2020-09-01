/*
 * LeftOuterJoinTarget.cpp
 *
 *  Created on: 2020/08/08
 *      Author: iizuka
 */

#include "scan_table/LeftOuterJoinTarget.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionsHolder.h"

#include "vm/VirtualMachine.h"

#include "scan_planner_scanner_ctx_join/ScanJoinContextHolder.h"
#include "scan_planner_scanner_ctx/AbstractJoinCandidate.h"
#include "scan_planner_scanner_ctx/JoinCandidateHolder.h"

#include "scan_condition/AbstractScanCondition.h"
#include "scan_condition/RootScanCondition.h"

namespace codablecash {

LeftOuterJoinTarget::LeftOuterJoinTarget() {

}

LeftOuterJoinTarget::~LeftOuterJoinTarget() {

}

const UnicodeString* LeftOuterJoinTarget::toString() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toString());

		this->str->append(L" LEFT JOIN ");

		this->str->append(this->right->toString());

		addConditionString();
	}

	return this->str;
}

AbstractScannerFactory* LeftOuterJoinTarget::getScanFactory(VirtualMachine* vm, SelectScanPlanner* planner) {
	ConditionsHolder* holder = planner->getConditions();


	ScanJoinContextHolder* contextHolder = new ScanJoinContextHolder(); __STP(contextHolder);

	ArrayList<AbstractScanTableTarget> list;
	this->collectScanTargets(vm, planner, &list);


	JoinCandidateHolder joinCandidates;
	if(this->cond != nullptr){
		this->cond->collectJoinCandidate(vm, planner, AbstractJoinCandidate::LEFT_OUTER, &joinCandidates);
	}

	RootScanCondition* root = holder->getRoot();

	// FIXME getScanFactory
	return nullptr;
}


} /* namespace codablecash */
