/*
 * ParenthesisScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/ParenthesisScanColumnTarget.h"

namespace codablecash {

ParenthesisScanColumnTarget::ParenthesisScanColumnTarget() {
	this->cond = nullptr;
}

ParenthesisScanColumnTarget::~ParenthesisScanColumnTarget() {
	delete this->cond;
}

void ParenthesisScanColumnTarget::setInnser(AbstractScanColumns* cond) noexcept {
	this->cond = cond;
}

} /* namespace codablecash */
