/*
 * MultipleIndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_index/MultipleIndexCandidate.h"
#include "scan_planner_scanner_ctx_index/IndexCandidate.h"
#include "scan_planner_scanner_ctx_index/OrIndexCandidate.h"

namespace codablecash {

MultipleIndexCandidate::MultipleIndexCandidate(const MultipleIndexCandidate& inst) {
	int maxLoop = inst.size();
	for(int i = 0; i != maxLoop; ++i){
		IndexCandidate* idx = inst.list.get(i);
		mul(idx);
	}
}

MultipleIndexCandidate::MultipleIndexCandidate() {

}

MultipleIndexCandidate::~MultipleIndexCandidate() {
	this->list.deleteElements();
}

AbstractIndexCandidate::IndexType MultipleIndexCandidate::getCandidateType() const noexcept {
	return AbstractIndexCandidate::IndexType::AND;
}

AbstractIndexCandidate* MultipleIndexCandidate::multiply(const AbstractIndexCandidate* other) const noexcept {
	AbstractIndexCandidate::IndexType candidateType = other->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const OrIndexCandidate* orCandidate = dynamic_cast<const OrIndexCandidate*>(other);
		return orCandidate->multiply(this);
	}

	MultipleIndexCandidate* candidate = new MultipleIndexCandidate();

	// copy self
	int maxLoop = size();
	for(int i = 0; i != maxLoop; ++i){
		const IndexCandidate* c = get(i);
		candidate->mul(c);
	}

	// other
	const AbstractIndexCandidateCollection* col = dynamic_cast<const AbstractIndexCandidateCollection*>(other);

	maxLoop = col->size();
	for(int i = 0; i != maxLoop; ++i){
		const IndexCandidate* c = col->get(i);
		candidate->mul(c);
	}

	return candidate;
}

AbstractIndexCandidate* MultipleIndexCandidate::copy() const noexcept {
	return new MultipleIndexCandidate(*this);
}

int MultipleIndexCandidate::size() const noexcept {
	return this->list.size();
}

const IndexCandidate* MultipleIndexCandidate::get(int i) const noexcept {
	return this->list.get(i);
}

void MultipleIndexCandidate::mul(const IndexCandidate* candidate) noexcept {
	this->list.addElement(new IndexCandidate(*candidate));
}

} /* namespace codablecash */
