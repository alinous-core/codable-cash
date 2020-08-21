/*
 * PlaceHolderScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/PlaceHolderScanColumnTarget.h"

namespace codablecash {

PlaceHolderScanColumnTarget::PlaceHolderScanColumnTarget(AbstractExpression* exp) {
	this->exp = exp;
}

PlaceHolderScanColumnTarget::~PlaceHolderScanColumnTarget() {
	this->exp = nullptr;
}

} /* namespace codablecash */
