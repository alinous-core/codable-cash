/*
 * JoinBranchCandidate.cpp
 *
 *  Created on: 2020/09/01
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/join/JoinOrCandidate.h"
#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidateCollection.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidate.h"

namespace codablecash {

JoinOrCandidate::JoinOrCandidate(const JoinOrCandidate& inst) : AbstractJoinCandidate(inst.joinType) {
	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJoinCandidateCollection* col = inst.list.get(i);
		AbstractJoinCandidateCollection* newCol = dynamic_cast<AbstractJoinCandidateCollection*>(col->copy());

		this->list.addElement(newCol);
	}
}

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

	JoinOrCandidate* newCond = new JoinOrCandidate(this->joinType);
	const AbstractJoinCandidateCollection* col = dynamic_cast<const AbstractJoinCandidateCollection*>(other);

	multiply(this, col, newCond);

	return newCond;
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

void JoinOrCandidate::add(const AbstractJoinCandidate* candidate) noexcept {
	JoinCandidate::CandidateType candidateType = candidate->getCandidateType();

	if(candidateType == JoinCandidate::CandidateType::OR){
		addOr(dynamic_cast<const JoinOrCandidate*>(candidate));
		return;
	}

	AbstractJoinCandidateCollection* col = dynamic_cast<AbstractJoinCandidateCollection*>(candidate->copy());
	this->list.addElement(col);
}

void JoinOrCandidate::addOr(const JoinOrCandidate* candidate) noexcept {
	int maxLoop = candidate->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJoinCandidateCollection* col = dynamic_cast<AbstractJoinCandidateCollection*>(candidate->list.get(i)->copy());

		this->list.addElement(col);
	}
}

AbstractJoinCandidate* JoinOrCandidate::copy() const noexcept {
	return new JoinOrCandidate(*this);
}

int JoinOrCandidate::size() const noexcept {
	return this->list.size();
}

const AbstractJoinCandidateCollection* JoinOrCandidate::get(int i) const noexcept {
	return this->list.get(i);
}

int JoinOrCandidate::getOverHeadScore(AbstractScanTableTarget* left, AbstractScanTableTarget* right) const noexcept {
	int score = 0;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJoinCandidateCollection* col = this->list.get(i);

		score += col->getOverHeadScore(left, right);
	}

	return score;
}

CdbTableIndex* JoinOrCandidate::getIndex(const AbstractScanTableTarget* right) const noexcept {
	return nullptr;
}

} /* namespace codablecash */
