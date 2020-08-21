/*
 * NotScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_logical/NotScanColumnTarget.h"

namespace codablecash {

NotScanColumnTarget::NotScanColumnTarget() {
	this->cond = nullptr;
}

NotScanColumnTarget::~NotScanColumnTarget() {
	delete this->cond;
}

void NotScanColumnTarget::setCond(AbstractScanColumnsTarget* cond) noexcept {
	this->cond = cond;
}

} /* namespace codablecash */
