/*
 * AndLogicalScanColumn.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_logical/AndLogicalScanColumnTarget.h"

namespace codablecash {

AndLogicalScanColumnTarget::AndLogicalScanColumnTarget() {

}

AndLogicalScanColumnTarget::~AndLogicalScanColumnTarget() {
	this->list.deleteElements();
}

void AndLogicalScanColumnTarget::addCondition(AbstractScanColumns* cond) noexcept {
	this->list.addElement(cond);
}

} /* namespace codablecash */
