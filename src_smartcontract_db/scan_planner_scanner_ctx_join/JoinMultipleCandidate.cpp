/*
 * JoinMuntipleCandidate.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/JoinMultipleCandidate.h"
#include "scan_planner_scanner_ctx_join/JoinCandidate.h"

namespace codablecash {

JoinMultipleCandidate::JoinMultipleCandidate(int joinType) : AbstractJoinCandidate(joinType) {
}

JoinMultipleCandidate::~JoinMultipleCandidate() {
	this->list.deleteElements();
}

AbstractJoinCandidate::CandidateType JoinMultipleCandidate::getCandidateType() const noexcept {
	return AbstractJoinCandidate::CandidateType::AND;
}

AbstractJoinCandidate* JoinMultipleCandidate::multiply(const AbstractJoinCandidate* other) const noexcept {
}

} /* namespace codablecash */
