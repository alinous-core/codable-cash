/*
 * BooleanScanParam.cpp
 *
 *  Created on: 2020/07/27
 *      Author: iizuka
 */

#include "scan_condition_params/BooleanScanParam.h"

#include "base/UnicodeString.h"

namespace codablecash {

const UnicodeString BooleanScanParam::TRUE(L"true");
const UnicodeString BooleanScanParam::FALSE(L"false");

BooleanScanParam::BooleanScanParam(const BooleanScanParam& inst) {
	this->value = inst.value;
}


BooleanScanParam::BooleanScanParam(bool value) {
	this->value = value;
}

BooleanScanParam::~BooleanScanParam() {

}

const UnicodeString* BooleanScanParam::toStringCode() noexcept {
	return this->value ? &TRUE: &FALSE;
}

IValueProvider* BooleanScanParam::clone() const noexcept {
	return new BooleanScanParam(*this);
}

} /* namespace codablecash */
