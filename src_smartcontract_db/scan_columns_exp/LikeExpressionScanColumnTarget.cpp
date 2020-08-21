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

void LikeExpressionScanColumnTarget::setLeft(AbstractScanColumns* left) noexcept {
	this->left = left;
}

void LikeExpressionScanColumnTarget::setRight(AbstractScanColumns* right) noexcept {
	this->right = right;
}

void LikeExpressionScanColumnTarget::setEscape(AbstractScanColumns* escape) noexcept {
	this->escape = escape;
}


} /* namespace codablecash */
