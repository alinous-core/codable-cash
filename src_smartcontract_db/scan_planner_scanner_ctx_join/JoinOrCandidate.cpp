/*
 * JoinBranchCandidate.cpp
 *
 *  Created on: 2020/09/01
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/JoinOrCandidate.h"
#include "scan_planner_scanner_ctx_join/JoinMultipleCandidate.h"

namespace codablecash {

JoinOrCandidate::JoinOrCandidate(int joinType) : AbstractJoinCandidate(joinType) {

}

JoinOrCandidate::~JoinOrCandidate() {
	this->list.deleteElements();
}

AbstractJoinCandidate::CandidateType JoinOrCandidate::getCandidateType() const noexcept {
	return AbstractJoinCandidate::CandidateType::OR;
}

AbstractJoinCandidate* JoinOrCandidate::multiply(const AbstractJoinCandidate* other) const noexcept {
}

} /* namespace codablecash */
