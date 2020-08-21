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

void ExpressionListScanColumnTarget::addElement(AbstractScanColumnsTarget* val) noexcept {
	this->list.addElement(val);
}

const UnicodeString* ExpressionListScanColumnTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
