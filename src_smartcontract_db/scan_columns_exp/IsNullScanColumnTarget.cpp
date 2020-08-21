/*
 * IsNullScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/IsNullScanColumnTarget.h"

namespace codablecash {

IsNullScanColumnTarget::IsNullScanColumnTarget() {
	this->cond = nullptr;
	this->notnull = false;
}

IsNullScanColumnTarget::~IsNullScanColumnTarget() {
	delete this->cond;
}

void IsNullScanColumnTarget::setCondition(AbstractScanColumnsTarget* cond) noexcept {
	this->cond = cond;
}

void IsNullScanColumnTarget::setIsNull(bool notnull) noexcept {
	this->notnull = notnull;
}

} /* namespace codablecash */
