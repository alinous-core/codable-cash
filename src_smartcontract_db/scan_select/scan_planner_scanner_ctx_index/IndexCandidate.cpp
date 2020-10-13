/*
 * IndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner_scanner_ctx_index/IndexCandidate.h"
#include "scan_select/scan_planner_scanner_ctx_index/OrIndexCandidate.h"
#include "scan_select/scan_planner_scanner_ctx_index/MultipleIndexCandidate.h"

namespace codablecash {

IndexCandidate::IndexCandidate(const IndexCandidate& inst) {

}

IndexCandidate::IndexCandidate() {

}

IndexCandidate::~IndexCandidate() {

}

AbstractIndexCandidate::IndexType IndexCandidate::getCandidateType() const noexcept {
	return AbstractIndexCandidate::IndexType::EQUALS;
}

AbstractIndexCandidate* IndexCandidate::multiply(const AbstractIndexCandidate* other) const noexcept {
	AbstractIndexCandidate::IndexType candidateType = other->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const OrIndexCandidate* orCandidate = dynamic_cast<const OrIndexCandidate*>(other);
		return orCandidate->multiply(this);
	}

	MultipleIndexCandidate* candidate = new MultipleIndexCandidate();

	const AbstractIndexCandidateCollection* col = dynamic_cast<const AbstractIndexCandidateCollection*>(other);

	int maxLoop = col->size();
	for(int i = 0; i != maxLoop; ++i){
		const IndexCandidate* c = col->get(i);
		candidate->mul(c);
	}

	return candidate;
}

AbstractIndexCandidate* IndexCandidate::copy() const noexcept {
	return new IndexCandidate(*this);
}

int IndexCandidate::size() const noexcept {
	return 1;
}

const IndexCandidate* IndexCandidate::get(int i) const noexcept {
	return this;
}

} /* namespace codablecash */
