/*
 * JoinCandidateHolder.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/JoinCandidateHolder.h"
#include "scan_planner_scanner_ctx_join/AbstractJoinCandidate.h"
#include "scan_planner_scanner_ctx_join/JoinCandidate.h"


namespace codablecash {

JoinCandidateHolder::JoinCandidateHolder(const AbstractScanTableTarget* left, const AbstractScanTableTarget* right) {
	this->left = left;
	this->right = right;
}

JoinCandidateHolder::~JoinCandidateHolder() {
	this->stack.deleteElements();
	this->leftOuterJoin.deleteElements();
	this->innerJoin.deleteElements();

	this->left = nullptr;
	this->right = nullptr;
}

bool JoinCandidateHolder::isEmpty() const noexcept {
	return this->stack.isEmpty();
}

void JoinCandidateHolder::push(AbstractJoinCandidate* candidate) noexcept {
	this->stack.addElement(candidate);
}

AbstractJoinCandidate* JoinCandidateHolder::pop() noexcept {
	int index = this->stack.size() - 1;
	return this->stack.remove(index);
}

bool JoinCandidateHolder::isJoinCondition(JoinCandidate* candidate) const noexcept {


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

} /* namespace codablecash */
