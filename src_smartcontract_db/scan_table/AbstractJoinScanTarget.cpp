/*
 * AbstractJoinScanTarget.cpp
 *
 *  Created on: 2020/08/09
 *      Author: iizuka
 */

#include "scan_table/AbstractJoinScanTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

AbstractJoinScanTarget::AbstractJoinScanTarget() {
	this->left = nullptr;
	this->right = nullptr;

	this->str = nullptr;
}

AbstractJoinScanTarget::~AbstractJoinScanTarget() {
	delete this->left;
	delete this->right;

	resetStr();
}

void AbstractJoinScanTarget::setLeft(AbstractScanTableTarget* left) noexcept {
	this->left = left;
	resetStr();
}

void AbstractJoinScanTarget::setRight(AbstractScanTableTarget* right) noexcept {
	this->right = right;
	resetStr();
}

void AbstractJoinScanTarget::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}


} /* namespace codablecash */
