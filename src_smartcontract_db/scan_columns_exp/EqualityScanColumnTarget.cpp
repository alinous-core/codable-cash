/*
 * EqualityScanColumnTarget.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_exp/EqualityScanColumnTarget.h"

namespace codablecash {

EqualityScanColumnTarget::EqualityScanColumnTarget() {
	this->left = nullptr;
	this->right = nullptr;
}

EqualityScanColumnTarget::~EqualityScanColumnTarget() {
	delete this->left;
	delete this->right;
}

void EqualityScanColumnTarget::setLeft(AbstractScanColumnsTarget* element) noexcept {
	this->left = element;
}

void EqualityScanColumnTarget::setRight(AbstractScanColumnsTarget* element) noexcept {
	this->right = element;
}


} /* namespace codablecash */
