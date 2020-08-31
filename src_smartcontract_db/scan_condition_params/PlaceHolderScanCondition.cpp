/*
 * PlaceHolderScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_params/PlaceHolderScanCondition.h"

#include "base/UnicodeString.h"

namespace codablecash {

PlaceHolderScanCondition::PlaceHolderScanCondition(const PlaceHolderScanCondition& inst) {
	this->exp = inst.exp;
	this->str = nullptr;
}

PlaceHolderScanCondition::PlaceHolderScanCondition(AbstractExpression* exp) {
	this->exp = exp;
	this->str = nullptr;
}

PlaceHolderScanCondition::~PlaceHolderScanCondition() {
	resetStr();
}

const UnicodeString* PlaceHolderScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"${}");
	}

	return this->str;
}

void PlaceHolderScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

AbstractScanConditionParameter* PlaceHolderScanCondition::clone() const noexcept {
	return new PlaceHolderScanCondition(*this);
}

} /* namespace codablecash */
