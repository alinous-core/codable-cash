/*
 * JoinBranchCandidate.cpp
 *
 *  Created on: 2020/09/01
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/JoinOrCandidate.h"
#include "scan_planner_scanner_ctx_join/AbstractJoinCandidateCollection.h"
#include "scan_planner_scanner_ctx_join/JoinCandidate.h"

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
	JoinCandidate::CandidateType candidateType = other->getCandidateType();

	if(candidateType == JoinCandidate::CandidateType::OR){
		const JoinOrCandidate* orCandidate = dynamic_cast<const JoinOrCandidate*>(other);
		return multiplyOr(orCandidate);
	}
}

AbstractJoinCandidate* JoinOrCandidate::multiplyOr(const JoinOrCandidate* other) const noexcept {
	JoinOrCandidate* newCond = new JoinOrCandidate(this->joinType);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJoinCandidateCollection* col = this->list.get(i);

		multiply(other, col, newCond);
	}

	return newCond;
}

void JoinOrCandidate::multiply(const JoinOrCandidate* other,
		const AbstractJoinCandidateCollection* col,
		JoinOrCandidate* newCond) const noexcept {
	int maxLoop = other->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJoinCandidateCollection* c = other->list.get(i);

		AbstractJoinCandidate* newC = c->multiply(col);
		AbstractJoinCandidateCollection* newCollection = dynamic_cast<AbstractJoinCandidateCollection*>(newC);

		newCond->list.addElement(newCollection);
	}
}


} /* namespace codablecash */
