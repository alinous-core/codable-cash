/*
 * IndexRangeCandidate.cpp
 *
 *  Created on: 2020/11/16
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/IndexRangeCandidate.h"

namespace codablecash {

IndexRangeCandidate::IndexRangeCandidate() : IndexCandidate(IndexType::RANGE) {
	this->topValue = nullptr;
	this->bottomEq = false;
	this->topEq = false;
}

IndexRangeCandidate::~IndexRangeCandidate() {
	this->topValue = nullptr;
}

} /* namespace codablecash */
