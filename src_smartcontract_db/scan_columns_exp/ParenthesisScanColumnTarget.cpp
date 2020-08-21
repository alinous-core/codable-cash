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

void ParenthesisScanColumnTarget::setInnser(AbstractScanColumnsTarget* cond) noexcept {
	this->cond = cond;
}

const UnicodeString* ParenthesisScanColumnTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
