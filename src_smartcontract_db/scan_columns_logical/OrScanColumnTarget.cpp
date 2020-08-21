/*
 * OrlScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_logical/OrScanColumnTarget.h"

namespace codablecash {

OrScanColumnTarget::OrScanColumnTarget() {

}

OrScanColumnTarget::~OrScanColumnTarget() {
	this->list.deleteElements();
}

void OrScanColumnTarget::addCondition(AbstractScanColumns* cond) noexcept {
	this->list.addElement(cond);
}


} /* namespace codablecash */
