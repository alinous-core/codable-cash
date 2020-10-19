/*
 * JoinMuntipleCandidate.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/join/JoinMultipleCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinOrCandidate.h"

namespace codablecash {

codablecash::JoinMultipleCandidate::JoinMultipleCandidate(const JoinMultipleCandidate& inst) : AbstractJoinCandidateCollection(joinType) {
	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		const JoinCandidate* candidate = inst.list.get(i);

		this->list.addElement(new JoinCandidate(*candidate));
	}
}

JoinMultipleCandidate::JoinMultipleCandidate(int joinType) : AbstractJoinCandidateCollection(joinType) {
}

JoinMultipleCandidate::~JoinMultipleCandidate() {
	this->list.deleteElements();
}

AbstractJoinCandidate::CandidateType JoinMultipleCandidate::getCandidateType() const noexcept {
	return AbstractJoinCandidate::CandidateType::AND;
}

AbstractJoinCandidate* JoinMultipleCandidate::multiply(const AbstractJoinCandidate* other) const noexcept {
	JoinCandidate::CandidateType candidateType = other->getCandidateType();

	if(candidateType == JoinCandidate::CandidateType::OR){
		const JoinOrCandidate* orCandidate = dynamic_cast<const JoinOrCandidate*>(other);
		return orCandidate->multiply(this);
	}

	JoinMultipleCandidate* candidate = new JoinMultipleCandidate(this->joinType);

	// copy self
	int maxLoop = size();
	for(int i = 0; i != maxLoop; ++i){
		const JoinCandidate* c = get(i);
		candidate->mul(c);
	}

	// other
	const AbstractJoinCandidateCollection* col = dynamic_cast<const AbstractJoinCandidateCollection*>(other);

	maxLoop = col->size();
	for(int i = 0; i != maxLoop; ++i){
		const JoinCandidate* c = col->get(i);
		candidate->mul(c);
	}

	return candidate;
}

int JoinMultipleCandidate::size() const noexcept {
	return this->list.size();
}

const JoinCandidate* JoinMultipleCandidate::get(int i) const noexcept {
	return this->list.get(i);
}

AbstractJoinCandidate* JoinMultipleCandidate::copy() const noexcept {
	return new JoinMultipleCandidate(*this);
}

void codablecash::JoinMultipleCandidate::mul(const JoinCandidate* candidate) noexcept {
	this->list.addElement(new JoinCandidate(*candidate));
}

int JoinMultipleCandidate::getOverHeadScore(AbstractScanTableTarget* left, AbstractScanTableTarget* right) const noexcept {

	int maxLoop = this->list.size();

	// TODO
	return 1;
}



} /* namespace codablecash */
