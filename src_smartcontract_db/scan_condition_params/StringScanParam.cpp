/*
 * StringScanParam.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_condition_params/StringScanParam.h"

#include "base/UnicodeString.h"


namespace codablecash {

StringScanParam::StringScanParam(const UnicodeString* str) {
	this->value = new UnicodeString(str);
}

StringScanParam::~StringScanParam() {
	delete this->value;
}

} /* namespace codablecash */
