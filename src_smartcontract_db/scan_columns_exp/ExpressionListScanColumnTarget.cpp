/*
 * ExpressionListScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/ExpressionListScanColumnTarget.h"

namespace codablecash {

ExpressionListScanColumnTarget::ExpressionListScanColumnTarget() {

}

ExpressionListScanColumnTarget::~ExpressionListScanColumnTarget() {
	this->list.deleteElements();
}

void ExpressionListScanColumnTarget::addElement(AbstractScanColumns* val) noexcept {
	this->list.addElement(val);
}

} /* namespace codablecash */
