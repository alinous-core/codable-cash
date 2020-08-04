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
	this->notnull = false;
}

IsNullScanCondition::~IsNullScanCondition() {
	delete this->cond;
	resetStr();
}

void IsNullScanCondition::setCondition(IValueProvider* cond) noexcept {
	this->cond = cond;
	resetStr();
}

void IsNullScanCondition::setIsNull(bool notnull) noexcept {
	this->notnull = notnull;
}

const UnicodeString* IsNullScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		AbstractScanConditionElement* element = dynamic_cast<AbstractScanConditionElement*>(this->cond);
		this->str->append(element->toStringCode());

		this->str = new UnicodeString(L" IS ");

		if(this->notnull){
			this->str = new UnicodeString(L" NOT ");
		}

		this->str = new UnicodeString(L" NULL");
	}

	return this->str;
}

void IsNullScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */