/*
 * BooleanLiteralColumnParam.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_params/BooleanLiteralColumnParam.h"

namespace codablecash {

BooleanLiteralColumnParam::BooleanLiteralColumnParam(bool value) {
	this->value = value;
}

BooleanLiteralColumnParam::~BooleanLiteralColumnParam() {

}

} /* namespace codablecash */
