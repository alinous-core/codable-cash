/*
 * MultiplicativeExpressionScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_arithmetic/MultiplicativeExpressionScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

MultiplicativeExpressionScanColumnTarget::MultiplicativeExpressionScanColumnTarget() : operations(2) {

}

MultiplicativeExpressionScanColumnTarget::~MultiplicativeExpressionScanColumnTarget() {
	this->list.deleteElements();
}

void MultiplicativeExpressionScanColumnTarget::addOperand(AbstractScanColumnsTarget* vp) noexcept {
	this->list.addElement(vp);
}

void MultiplicativeExpressionScanColumnTarget::addOperator(uint8_t op) noexcept {
	this->operations.addElement(op);
}

const UnicodeString* MultiplicativeExpressionScanColumnTarget::toStringCode() {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
