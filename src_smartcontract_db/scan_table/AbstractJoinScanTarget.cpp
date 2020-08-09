/*
 * AbstractJoinScanTarget.cpp
 *
 *  Created on: 2020/08/09
 *      Author: iizuka
 */

#include "scan_table/AbstractJoinScanTarget.h"

namespace codablecash {

AbstractJoinScanTarget::AbstractJoinScanTarget() {
	this->left = nullptr;
	this->right = nullptr;
}

AbstractJoinScanTarget::~AbstractJoinScanTarget() {
	delete this->left;
	delete this->right;
}

void AbstractJoinScanTarget::setLeft(AbstractScanTableTarget* left) noexcept {
	this->left = left;
}

void AbstractJoinScanTarget::setRight(AbstractScanTableTarget* right) noexcept {
	this->right = right;
}

} /* namespace codablecash */
