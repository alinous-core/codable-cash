/*
 * AndLogicalScanColumn.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_logical/AndLogicalScanColumn.h"

namespace codablecash {

AndLogicalScanColumn::AndLogicalScanColumn() {

}

AndLogicalScanColumn::~AndLogicalScanColumn() {
	this->list.deleteElements();
}

void AndLogicalScanColumn::addCondition(AbstractScanColumns* cond) noexcept {
	this->list.addElement(cond);
}

} /* namespace codablecash */
