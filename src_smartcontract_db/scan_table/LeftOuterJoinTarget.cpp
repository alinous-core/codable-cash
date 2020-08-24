/*
 * LeftOuterJoinTarget.cpp
 *
 *  Created on: 2020/08/08
 *      Author: iizuka
 */

#include "scan_table/LeftOuterJoinTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

LeftOuterJoinTarget::LeftOuterJoinTarget() {

}

LeftOuterJoinTarget::~LeftOuterJoinTarget() {

}

const UnicodeString* LeftOuterJoinTarget::toString() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toString());

		this->str->append(L" LEFT JOIN ");

		this->str->append(this->right->toString());

		addConditionString();
	}

	return this->str;
}

IJoinLeftSource* LeftOuterJoinTarget::getLeftSource(VirtualMachine* vm) {
	// FIXME getLeftSource
}

IJoinLeftSource* LeftOuterJoinTarget::getRightSource(VirtualMachine* vm) {
	// FIXME getRightSource
}

} /* namespace codablecash */
