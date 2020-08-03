/*
 * NumericScanParam.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_condition_params/NumericScanParam.h"

using alinous::Long;

#include "base/Long.h"

namespace codablecash {

NumericScanParam::NumericScanParam(int64_t longv) {
	this->value = longv;
	this->str = nullptr;
}

NumericScanParam::~NumericScanParam() {
	delete this->str;
}

const UnicodeString* NumericScanParam::toStringCode() noexcept {
	if(str == nullptr){
		delete this->str;
		this->str = Long::toString(this->value, 10);
	}

	return this->str;
}

} /* namespace codablecash */
