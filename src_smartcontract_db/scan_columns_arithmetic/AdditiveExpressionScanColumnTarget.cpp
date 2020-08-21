/*
 * AdditiveExpressionScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_arithmetic/AdditiveExpressionScanColumnTarget.h"

namespace codablecash {

AdditiveExpressionScanColumnTarget::AdditiveExpressionScanColumnTarget() : operations(2) {

}

AdditiveExpressionScanColumnTarget::~AdditiveExpressionScanColumnTarget() {
	this->list.deleteElements();

}

void AdditiveExpressionScanColumnTarget::addOperand(AbstractScanColumnsTarget* vp) noexcept {
	this->list.addElement(vp);
}

void AdditiveExpressionScanColumnTarget::addOperator(uint8_t op) noexcept {
	this->operations.addElement(op);
}

const UnicodeString* AdditiveExpressionScanColumnTarget::toStringCode() {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
