/*
 * JoinCandidateHolder.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/join/JoinCandidateHolder.h"
#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidateStack.h"

#include "scan_select/scan_table/AbstractScanTableTarget.h"

namespace codablecash {

JoinCandidateHolder::JoinCandidateHolder(const AbstractScanTableTarget* left, const AbstractScanTableTarget* right) {
	this->left = left;
	this->right = right;

	this->stack = new JoinCandidateStack();
}

JoinCandidateHolder::~JoinCandidateHolder() {
	this->leftOuterJoin.deleteElements();
	this->innerJoin.deleteElements();

	this->left = nullptr;
	this->right = nullptr;

	delete this->stack;
}

bool JoinCandidateHolder::isEmpty() const noexcept {
	return this->stack->isEmpty();
}

void JoinCandidateHolder::push(AbstractJoinCandidate* candidate) noexcept {
	this->stack->push(candidate);
}

AbstractJoinCandidate* JoinCandidateHolder::pop() noexcept {
	return this->stack->pop();
}

bool JoinCandidateHolder::isJoinCondition(JoinCandidate* candidate) const noexcept {
	const AbstractScanTableTarget* leftTarget = candidate->getLeftTarget();
	const AbstractScanTableTarget* rightTarget = candidate->getRightTarget();

	return (this->left->hasTarget(leftTarget) && this->right->hasTarget(rightTarget))
			|| (this->left->hasTarget(rightTarget) && this->right->hasTarget(leftTarget));
}

void JoinCandidateHolder::addJoinCandidate(AbstractJoinCandidate* candidate) noexcept {
	int joinType = candidate->getJoinType();

	if(joinType == AbstractJoinCandidate::LEFT_OUTER){
		this->leftOuterJoin.addElement(candidate);
	}
	else{
		this->innerJoin.addElement(candidate);
	}
}

bool JoinCandidateHolder::isInnerJoin() const noexcept {
	return !this->innerJoin.isEmpty();
}

const AbstractJoinCandidate* JoinCandidateHolder::getBestCandidate(AbstractScanTableTarget* left, AbstractScanTableTarget* right) const noexcept {
	if(isInnerJoin()){
		return getBestFromList(&this->innerJoin, left, right);
	}

	return getBestFromList(&this->leftOuterJoin, left, right);
}

const AbstractJoinCandidate* JoinCandidateHolder::getBestFromList(
		const ArrayList<AbstractJoinCandidate>* list, AbstractScanTableTarget* left, AbstractScanTableTarget* right) const noexcept {
	AbstractJoinCandidate* candidate = nullptr;
	int score = 0;

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJoinCandidate* cn = list->get(i);

		int currentScore = cn->getOverHeadScore(left, right);
		if(candidate == nullptr || currentScore < score){
			score = currentScore;
			candidate = cn;
		}
	}

	return candidate;
}

} /* namespace codablecash */
