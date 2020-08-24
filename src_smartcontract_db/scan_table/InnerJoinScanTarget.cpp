/*
 * InnerJoinScanTarget.cpp
 *
 *  Created on: 2020/08/08
 *      Author: iizuka
 */

#include "scan_table/InnerJoinScanTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

InnerJoinScanTarget::InnerJoinScanTarget() {

}

InnerJoinScanTarget::~InnerJoinScanTarget() {

}

const UnicodeString* InnerJoinScanTarget::toString() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toString());

		this->str->append(L" INNER JOIN ");

		this->str->append(this->right->toString());

		addConditionString();
	}

	return this->str;
}

IJoinLeftSource* InnerJoinScanTarget::getLeftSource(VirtualMachine* vm) {
}

IJoinLeftSource* InnerJoinScanTarget::getRightSource(VirtualMachine* vm) {
}


} /* namespace codablecash */
