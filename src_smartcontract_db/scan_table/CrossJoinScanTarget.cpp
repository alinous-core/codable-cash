/*
 * CrossJoinScanTarget.cpp
 *
 *  Created on: 2020/08/08
 *      Author: iizuka
 */

#include "scan_table/CrossJoinScanTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

CrossJoinScanTarget::CrossJoinScanTarget() {

}

CrossJoinScanTarget::~CrossJoinScanTarget() {

}

const UnicodeString* CrossJoinScanTarget::toString() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toString());

		this->str->append(L" CROSS JOIN ");

		this->str->append(this->right->toString());

		addConditionString();
	}

	return this->str;
}

IJoinLeftSource* codablecash::CrossJoinScanTarget::getLeftSource(VirtualMachine* vm) {
	// FIXME getLeftSource
}

IJoinLeftSource* codablecash::CrossJoinScanTarget::getRightSource(VirtualMachine* vm) {
	// FIXME getRightSource
}


} /* namespace codablecash */
