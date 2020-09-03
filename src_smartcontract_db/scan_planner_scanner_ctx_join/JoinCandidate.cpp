/*
 * JoinCandidate.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/JoinCandidate.h"

#include "scan_table/AbstractScanTableTarget.h"

#include "scan_condition_params/ColumnIdentifierScanParam.h"

#include "scan_planner_scanner_ctx_join/JoinOrCandidate.h"
#include "scan_planner_scanner_ctx_join/JoinMultipleCandidate.h"

namespace codablecash {

JoinCandidate::JoinCandidate(int joinType, ColumnIdentifierScanParam* left, ColumnIdentifierScanParam* right) : AbstractJoinCandidate(joinType) {
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


}

} /* namespace codablecash */
