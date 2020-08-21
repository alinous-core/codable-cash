/*
 * LikeExpression.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/LikeExpressionScanColumnTarget.h"

namespace codablecash {

LikeExpressionScanColumnTarget::LikeExpressionScanColumnTarget() {
	this->left = nullptr;
	this->right = nullptr;
	this->escape = nullptr;
}

LikeExpressionScanColumnTarget::~LikeExpressionScanColumnTarget() {
	delete this->left;
	delete this->right;
	delete this->escape;
}

void LikeExpressionScanColumnTarget::setLeft(AbstractScanColumnsTarget* left) noexcept {
	this->left = left;
}

void LikeExpressionScanColumnTarget::setRight(AbstractScanColumnsTarget* right) noexcept {
	this->right = right;
}

void LikeExpressionScanColumnTarget::setEscape(AbstractScanColumnsTarget* escape) noexcept {
	this->escape = escape;
}

const UnicodeString* LikeExpressionScanColumnTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
