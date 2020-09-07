/*
 * MultipleIndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_index/MultipleIndexCandidate.h"

namespace codablecash {

MultipleIndexCandidate::MultipleIndexCandidate() {

}

MultipleIndexCandidate::~MultipleIndexCandidate() {

}

AbstractIndexCandidate::IndexType MultipleIndexCandidate::getCandidateType() const noexcept {
	return AbstractIndexCandidate::IndexType::AND;
}

} /* namespace codablecash */
