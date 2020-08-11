/*
 * RightOuterJoinScanTarget.cpp
 *
 *  Created on: 2020/08/09
 *      Author: iizuka
 */

#include "scan_table/RightOuterJoinScanTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

RightOuterJoinScanTarget::RightOuterJoinScanTarget() {

}

RightOuterJoinScanTarget::~RightOuterJoinScanTarget() {

}

void RightOuterJoinScanTarget::setLeft(AbstractScanTableTarget* left) noexcept {
	this->right = left;
	resetStr();
}

void RightOuterJoinScanTarget::setRight(AbstractScanTableTarget* right) noexcept {
	this->left = right;
	resetStr();
}

const UnicodeString* RightOuterJoinScanTarget::toString() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		this->str->append(this->right->toString());

		this->str->append(L" RIGHT JOIN ");

		this->str->append(this->left->toString());

		addConditionString();
	}

	return this->str;
}

} /* namespace codablecash */
