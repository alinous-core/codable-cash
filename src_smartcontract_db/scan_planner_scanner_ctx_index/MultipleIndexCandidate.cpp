/*
 * MultipleIndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_index/MultipleIndexCandidate.h"

#include "scan_planner_scanner_ctx_index/IndexCandidate.h"

namespace codablecash {

MultipleIndexCandidate::MultipleIndexCandidate() {

}

MultipleIndexCandidate::~MultipleIndexCandidate() {
	this->list.deleteElements();
}

AbstractIndexCandidate::IndexType MultipleIndexCandidate::getCandidateType() const noexcept {
	return AbstractIndexCandidate::IndexType::AND;
}

AbstractIndexCandidate* MultipleIndexCandidate::multiply(const AbstractIndexCandidate* other) const noexcept {
}

AbstractIndexCandidate* MultipleIndexCandidate::copy() const noexcept {
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
