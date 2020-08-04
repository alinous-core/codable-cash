/*
 * IsNullScanCondition.cpp
 *
 *  Created on: 2020/08/04
 *      Author: iizuka
 */

#include "scan_condition_exp/IsNullScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_condition/IValueProvider.h"

namespace codablecash {

IsNullScanCondition::IsNullScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_IS_NULL) {
	this->cond = nullptr;
	this->str = nullptr;
}

IsNullScanCondition::~IsNullScanCondition() {
	delete this->cond;
	resetStr();
}

void IsNullScanCondition::setCondition(IValueProvider* cond) noexcept {
	this->cond = cond;
	resetStr();
}

const UnicodeString* IsNullScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){

	}
}

void IsNullScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
