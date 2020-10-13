/*
 * JoinCandidate.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_select/scan_planner_scanner_ctx_join/JoinCandidate.h"

#include "scan_select/scan_table/AbstractScanTableTarget.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "scan_select/scan_planner_scanner_ctx_join/JoinOrCandidate.h"
#include "scan_select/scan_planner_scanner_ctx_join/JoinMultipleCandidate.h"

namespace codablecash {

JoinCandidate::JoinCandidate(const JoinCandidate& inst) : AbstractJoinCandidateCollection(inst.joinType) {
	this->left = dynamic_cast<ColumnIdentifierScanParam*>(inst.left->clone());
	this->right = dynamic_cast<ColumnIdentifierScanParam*>(inst.right->clone());
}


JoinCandidate::JoinCandidate(int joinType, ColumnIdentifierScanParam* left, ColumnIdentifierScanParam* right) : AbstractJoinCandidateCollection(joinType) {
	this->left = dynamic_cast<ColumnIdentifierScanParam*>(left->clone());
	this->right = dynamic_cast<ColumnIdentifierScanParam*>(right->clone());
}

JoinCandidate::~JoinCandidate() {
	delete this->left;
	delete this->right;
}

const AbstractScanTableTarget* JoinCandidate::getLeftTarget() const noexcept {
	return this->left->getTarget();
}

const AbstractScanTableTarget* JoinCandidate::getRightTarget() const noexcept {
	return this->right->getTarget();
}

JoinCandidate::CandidateType JoinCandidate::getCandidateType() const noexcept {
	return JoinCandidate::CandidateType::EQUALS;
}

AbstractJoinCandidate* JoinCandidate::multiply(const AbstractJoinCandidate* other) const noexcept {
	JoinCandidate::CandidateType candidateType = other->getCandidateType();

	if(candidateType == JoinCandidate::CandidateType::OR){
		const JoinOrCandidate* orCandidate = dynamic_cast<const JoinOrCandidate*>(other);
		return orCandidate->multiply(this);
	}

	JoinMultipleCandidate* candidate = new JoinMultipleCandidate(this->joinType);

	const AbstractJoinCandidateCollection* col = dynamic_cast<const AbstractJoinCandidateCollection*>(other);

	int maxLoop = col->size();
	for(int i = 0; i != maxLoop; ++i){
		const JoinCandidate* c = col->get(i);
		candidate->mul(c);
	}

	return candidate;
}

int JoinCandidate::size() const noexcept {
	return 1;
}

const JoinCandidate* JoinCandidate::get(int i) const noexcept {
	return this;
}

AbstractJoinCandidate* JoinCandidate::copy() const noexcept {
	return new JoinCandidate(*this);
}


} /* namespace codablecash */
