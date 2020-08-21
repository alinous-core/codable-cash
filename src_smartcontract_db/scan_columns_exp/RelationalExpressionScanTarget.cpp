/*
 * RelationalExpressionScanTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/RelationalExpressionScanTarget.h"

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

} /* namespace codablecash */
