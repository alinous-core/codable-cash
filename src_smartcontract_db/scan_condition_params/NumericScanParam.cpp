/*
 * NumericScanParam.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_condition_params/NumericScanParam.h"

namespace codablecash {

NumericScanParam::NumericScanParam(int64_t longv) {
	this->value = longv;
}

NumericScanParam::~NumericScanParam() {

}

} /* namespace codablecash */
