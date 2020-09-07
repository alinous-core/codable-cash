/*
 * OrIndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_index/OrIndexCandidate.h"

namespace codablecash {

OrIndexCandidate::OrIndexCandidate() {

}

OrIndexCandidate::~OrIndexCandidate() {

}

AbstractIndexCandidate::IndexType OrIndexCandidate::getCandidateType() const noexcept {
	return AbstractIndexCandidate::IndexType::OR;
}

AbstractIndexCandidate* OrIndexCandidate::multiply(const AbstractIndexCandidate* other) const noexcept {
}

AbstractIndexCandidate* OrIndexCandidate::copy() const noexcept {
}

} /* namespace codablecash */
