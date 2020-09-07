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
}

AbstractIndexCandidate* OrIndexCandidate::copy() const noexcept {
	return new OrIndexCandidate(*this);
}

void OrIndexCandidate::add(const AbstractIndexCandidateCollection* candidate) noexcept {
	this->list.addElement(dynamic_cast<AbstractIndexCandidateCollection*>(candidate->copy()));
}

} /* namespace codablecash */
