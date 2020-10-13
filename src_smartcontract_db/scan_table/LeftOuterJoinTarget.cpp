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

#include "scan_planner_scanner_ctx/ScanJoinContextHolder.h"

#include "scan_planner_scanner_ctx_join/AbstractJoinCandidate.h"
#include "scan_planner_scanner_ctx_join/JoinCandidateHolder.h"

#include "scan_condition/AbstractScanCondition.h"
#include "scan_condition/RootScanCondition.h"

#include "scan_planner_scanner_ctx/FilterConditionDitector.h"

#include "scan_planner_scanner/InnerJoinScannerFactory.h"
#include "scan_planner_scanner/LeftJoinScannerFactory.h"

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

	JoinCandidateHolder joinCandidates(this->left, this->right);
	if(this->cond != nullptr){
		this->cond->collectJoinCandidate(vm, planner, AbstractJoinCandidate::LEFT_OUTER, &joinCandidates);
		while(!joinCandidates.isEmpty()){
			AbstractJoinCandidate* candidate = joinCandidates.pop();
			joinCandidates.addJoinCandidate(candidate);
		}
	}

	RootScanCondition* root = holder->getRoot();
	if(root != nullptr){
		root->collectJoinCandidate(vm, planner, AbstractJoinCandidate::INNER, &joinCandidates);
		while(!joinCandidates.isEmpty()){
			AbstractJoinCandidate* candidate = joinCandidates.pop();
			joinCandidates.addJoinCandidate(candidate);
		}
	}

	FilterConditionDitector filterDetector(vm, planner);
	filterDetector.detect(this);

	AbstractJoinScannerFactory* joinFactory = nullptr;
	if(joinCandidates.isInnerJoin()){
		joinFactory = new InnerJoinScannerFactory(this->metadata);
	}
	else{
		joinFactory = new LeftJoinScannerFactory(this->metadata);
	}

	AbstractJoinCandidate* bestCandidate = joinCandidates.getBestCandidate();


	AbstractScannerFactory* leftFactory = this->left->getScanFactory(vm, planner);
	joinFactory->setLeft(leftFactory);

	AbstractScannerFactory* rightFactory = this->right->getScanFactory(vm, planner);
	joinFactory->setRight(rightFactory);

	// FIXME getScanFactory
	return joinFactory;
}


} /* namespace codablecash */
