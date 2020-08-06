/*
 * InExpressionScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include <scan_condition_exp/InExpressionScanCondition.h>

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

namespace codablecash {

InExpressionScanCondition::InExpressionScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_IN) {
	this->str = nullptr;
}

InExpressionScanCondition::~InExpressionScanCondition() {

}

const UnicodeString* InExpressionScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){

	}

	return this->str;
}

void InExpressionScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
