/*
 * MultiplicativeExpressionScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_arithmetic/MultiplicativeExpressionScanColumnTarget.h"

namespace codablecash {

MultiplicativeExpressionScanColumnTarget::MultiplicativeExpressionScanColumnTarget() : operations(2) {

}

MultiplicativeExpressionScanColumnTarget::~MultiplicativeExpressionScanColumnTarget() {
	this->list.deleteElements();
}

void MultiplicativeExpressionScanColumnTarget::addOperand(AbstractScanColumns* vp) noexcept {
	this->list.addElement(vp);
}

void MultiplicativeExpressionScanColumnTarget::addOperator(uint8_t op) noexcept {
	this->operations.addElement(op);
}

} /* namespace codablecash */
