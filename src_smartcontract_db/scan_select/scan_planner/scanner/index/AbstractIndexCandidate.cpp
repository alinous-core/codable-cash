/*
 * AbstractIndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

#include "base/UnicodeString.h"

namespace codablecash {

AbstractIndexCandidate::AbstractIndexCandidate(IndexType indexType) {
	this->indexType = indexType;
	this->str = nullptr;
}

AbstractIndexCandidate::~AbstractIndexCandidate() {
	resetStr();
}

void AbstractIndexCandidate::resetStr() noexcept {
	delete this->str;
	this->str = nullptr;
}

} /* namespace codablecash */
