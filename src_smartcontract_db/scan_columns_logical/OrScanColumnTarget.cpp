/*
 * OrlScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_logical/OrScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

OrScanColumnTarget::OrScanColumnTarget() {

}

OrScanColumnTarget::~OrScanColumnTarget() {
	this->list.deleteElements();
}

void OrScanColumnTarget::addCondition(AbstractScanColumnsTarget* cond) noexcept {
	this->list.addElement(cond);
}

const UnicodeString* OrScanColumnTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
