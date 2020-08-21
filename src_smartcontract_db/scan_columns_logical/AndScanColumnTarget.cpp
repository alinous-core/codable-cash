/*
 * AndLogicalScanColumn.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_logical/AndScanColumnTarget.h"

namespace codablecash {

AndScanColumnTarget::AndScanColumnTarget() {

}

AndScanColumnTarget::~AndScanColumnTarget() {
	this->list.deleteElements();
}

void AndScanColumnTarget::addCondition(AbstractScanColumns* cond) noexcept {
	this->list.addElement(cond);
}

} /* namespace codablecash */
