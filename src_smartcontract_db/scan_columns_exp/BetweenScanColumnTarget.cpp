/*
 * BetweenScanColumnTarget.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_exp/BetweenScanColumnTarget.h"

#include "base/UnicodeString.h"

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

const UnicodeString* BetweenScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toStringCode());

		this->str->append(L" BETWEEN ");

		this->str->append(this->start->toStringCode());

		this->str->append(L" AND ");

		this->str->append(this->end->toStringCode());
	}

	return this->str;
}

} /* namespace codablecash */
