/*
 * ExpressionListScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_exp/ExpressionListScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

namespace codablecash {

ExpressionListScanCondition::ExpressionListScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_EXP_LIST) {
	this->str = nullptr;
}

ExpressionListScanCondition::~ExpressionListScanCondition() {
	resetStr();
}

const UnicodeString* ExpressionListScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){

	}

	return this->str;
}

void ExpressionListScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
