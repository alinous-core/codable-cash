/*
 * BetweenScanColumnTarget.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_exp/BetweenScanColumnTarget.h"

namespace codablecash {

BetweenScanColumnTarget::BetweenScanColumnTarget() {
	this->left = nullptr;
	this->start = nullptr;
	this->end = nullptr;
}

BetweenScanColumnTarget::~BetweenScanColumnTarget() {
	delete this->left;
	delete this->start;
	delete this->end;
}

void BetweenScanColumnTarget::setLeft(AbstractScanColumnsTarget* left) noexcept {
	this->left = left;
}

void BetweenScanColumnTarget::setStart(AbstractScanColumnsTarget* start) noexcept {
	this->start = start;
}

void BetweenScanColumnTarget::setEnd(AbstractScanColumnsTarget* end) noexcept {
	this->end = end;
}

} /* namespace codablecash */
