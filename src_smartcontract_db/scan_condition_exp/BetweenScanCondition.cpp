/*
 * BetweenScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_exp/BetweenScanCondition.h"

#include "scan_condition/IValueProvider.h"

#include "sc/CodeElement.h"

namespace codablecash {

BetweenScanCondition::BetweenScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_BETWEEN) {
	this->left = nullptr;
	this->start = nullptr;
	this->end = nullptr;
}

BetweenScanCondition::~BetweenScanCondition() {
	delete this->left;
	delete this->start;
	delete this->end;
}

void BetweenScanCondition::setLeft(IValueProvider* left) noexcept {
	this->left = left;
}

void BetweenScanCondition::setStart(IValueProvider* start) noexcept {
	this->start = start;
}

void BetweenScanCondition::setEnd(IValueProvider* end) noexcept {
	this->end = end;
}

} /* namespace codablecash */
