/*
 * RootScanCondition.cpp
 *
 *  Created on: 2020/06/14
 *      Author: iizuka
 */

#include "scan_condition/RootScanCondition.h"

namespace codablecash {

RootScanCondition::RootScanCondition() : AbstractScanCondition(0) {
	this->cond = nullptr;
}

RootScanCondition::~RootScanCondition() {
	delete this->cond;
}

void RootScanCondition::addCondition(AbstractScanCondition* cond) {
	delete this->cond;
	this->cond = cond;
}

const UnicodeString* RootScanCondition::toStringCode() noexcept {
	return this->cond->toStringCode();
}

} /* namespace codablecash */
