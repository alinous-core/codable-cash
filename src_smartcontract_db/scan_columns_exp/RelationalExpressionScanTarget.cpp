/*
 * RelationalExpressionScanTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/RelationalExpressionScanTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

RelationalExpressionScanTarget::RelationalExpressionScanTarget() {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

RelationalExpressionScanTarget::~RelationalExpressionScanTarget() {
	delete this->left;
	delete this->right;
}

void RelationalExpressionScanTarget::setLeft(AbstractScanColumnsTarget* element) noexcept {
	this->left = element;
}

void RelationalExpressionScanTarget::setRight(AbstractScanColumnsTarget* element) noexcept {
	this->right = element;
}

void RelationalExpressionScanTarget::setOp(uint8_t op) noexcept {
	this->op = op;
}

const UnicodeString* RelationalExpressionScanTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
