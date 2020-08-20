/*
 * NumberLiteralColumnParam.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_params/NumberLiteralColumnParam.h"

namespace codablecash {

NumberLiteralColumnParam::NumberLiteralColumnParam(int64_t longv) {
	this->longv = longv;
}

NumberLiteralColumnParam::~NumberLiteralColumnParam() {

}

} /* namespace codablecash */
