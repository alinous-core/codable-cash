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

void AndScanColumnTarget::addCondition(AbstractScanColumnsTarget* cond) noexcept {
	this->list.addElement(cond);
}

const UnicodeString* AndScanColumnTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
