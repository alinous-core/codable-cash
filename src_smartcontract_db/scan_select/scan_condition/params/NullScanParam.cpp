/*
 * NullScanParam.cpp
 *
 *  Created on: 2021/01/13
 *      Author: iizuka
 */

#include "scan_select/scan_condition/params/NullScanParam.h"

namespace codablecash {

NullScanParam::NullScanParam(const NullScanParam& inst) {

}

NullScanParam::NullScanParam() {
	// TODO Auto-generated constructor stub

}

NullScanParam::~NullScanParam() {

}

const UnicodeString* NullScanParam::toStringCode() noexcept {
}

IValueProvider* NullScanParam::clone() const noexcept {
	return new NullScanParam(*this);
}

} /* namespace codablecash */
