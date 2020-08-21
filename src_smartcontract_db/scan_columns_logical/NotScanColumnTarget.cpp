/*
 * NotScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_logical/NotScanColumnTarget.h"

#include "base/UnicodeString.h"

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

const UnicodeString* NotScanColumnTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
