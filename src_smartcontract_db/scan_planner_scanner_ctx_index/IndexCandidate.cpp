/*
 * IndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_index/IndexCandidate.h"

namespace codablecash {

IndexCandidate::IndexCandidate() {

}

IndexCandidate::~IndexCandidate() {

}

AbstractIndexCandidate::IndexType IndexCandidate::getCandidateType() const noexcept {
	return AbstractIndexCandidate::IndexType::EQUALS;
}

} /* namespace codablecash */
