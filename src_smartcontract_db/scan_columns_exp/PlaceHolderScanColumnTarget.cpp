/*
 * PlaceHolderScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/PlaceHolderScanColumnTarget.h"

namespace codablecash {

PlaceHolderScanColumnTarget::PlaceHolderScanColumnTarget(AbstractExpression* exp) {
	this->exp = exp;
}

PlaceHolderScanColumnTarget::~PlaceHolderScanColumnTarget() {
	this->exp = nullptr;
}

const UnicodeString* PlaceHolderScanColumnTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
