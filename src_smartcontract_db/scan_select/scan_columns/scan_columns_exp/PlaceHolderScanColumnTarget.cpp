/*
 * PlaceHolderScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_select/scan_columns/scan_columns_exp/PlaceHolderScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

PlaceHolderScanColumnTarget::PlaceHolderScanColumnTarget(AbstractExpression* exp) {
	this->exp = exp;
}

PlaceHolderScanColumnTarget::~PlaceHolderScanColumnTarget() {
	this->exp = nullptr;
}

const UnicodeString* PlaceHolderScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"${}");
	}

	return this->str;
}

void PlaceHolderScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
}


} /* namespace codablecash */
