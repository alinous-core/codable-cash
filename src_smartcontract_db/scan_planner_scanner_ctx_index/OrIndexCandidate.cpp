/*
 * OrIndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_index/OrIndexCandidate.h"

#include "scan_planner_scanner_ctx_index/AbstractIndexCandidateCollection.h"

namespace codablecash {

OrIndexCandidate::OrIndexCandidate(const OrIndexCandidate& inst) {
	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractIndexCandidateCollection* col = inst.list.get(i);
		add(col);
	}
}

OrIndexCandidate::OrIndexCandidate() {

}

OrIndexCandidate::~OrIndexCandidate() {
	this->list.deleteElements();
}

AbstractIndexCandidate::IndexType OrIndexCandidate::getCandidateType() const noexcept {
	return AbstractIndexCandidate::IndexType::OR;
}

AbstractIndexCandidate* OrIndexCandidate::multiply(const AbstractIndexCandidate* other) const noexcept {
	AbstractIndexCandidate::IndexType candidateType = other->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const OrIndexCandidate* orCandidate = dynamic_cast<const OrIndexCandidate*>(other);
		return multiplyOr(orCandidate);
	}

	OrIndexCandidate* newCond = new OrIndexCandidate();
	const AbstractIndexCandidateCollection* col = dynamic_cast<const AbstractIndexCandidateCollection*>(other);

	multiply(this, col, newCond);

	return newCond;
}

AbstractIndexCandidate* OrIndexCandidate::multiplyOr(const OrIndexCandidate* other) const noexcept {
	OrIndexCandidate* newCond = new OrIndexCandidate();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractIndexCandidateCollection* col = this->list.get(i);

		multiply(other, col, newCond);
	}

	return newCond;
}

void OrIndexCandidate::multiply(const OrIndexCandidate* other,
		const AbstractIndexCandidateCollection* col, OrIndexCandidate* newCond) const noexcept {
	int maxLoop = other->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractIndexCandidateCollection* c = other->list.get(i);

		AbstractIndexCandidate* newC = c->multiply(col);
		AbstractIndexCandidateCollection* newCollection = dynamic_cast<AbstractIndexCandidateCollection*>(newC);

		newCond->list.addElement(newCollection);
	}
}


AbstractIndexCandidate* OrIndexCandidate::copy() const noexcept {
	return new OrIndexCandidate(*this);
}

void OrIndexCandidate::add(const AbstractIndexCandidateCollection* candidate) noexcept {
	this->list.addElement(dynamic_cast<AbstractIndexCandidateCollection*>(candidate->copy()));
}
} /* namespace codablecash */
