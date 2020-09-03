/*
 * JoinMuntipleCandidate.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/JoinMultipleCandidate.h"
#include "scan_planner_scanner_ctx_join/JoinCandidate.h"

namespace codablecash {

JoinMultipleCandidate::JoinMultipleCandidate(int joinType) : AbstractJoinCandidateCollection(joinType) {
}

JoinMultipleCandidate::~JoinMultipleCandidate() {
	this->list.deleteElements();
}

AbstractJoinCandidate::CandidateType JoinMultipleCandidate::getCandidateType() const noexcept {
	return AbstractJoinCandidate::CandidateType::AND;
}

AbstractJoinCandidate* JoinMultipleCandidate::multiply(const AbstractJoinCandidate* other) const noexcept {
}

int JoinMultipleCandidate::size() const noexcept {
	return this->list.size();
}

const JoinCandidate* JoinMultipleCandidate::get(int i) const noexcept {
	return this->list.get(i);
}

void codablecash::JoinMultipleCandidate::mul(const JoinCandidate* candidate) noexcept {
	this->list.addElement(new JoinCandidate(*candidate));
}


} /* namespace codablecash */
