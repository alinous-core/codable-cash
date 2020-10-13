/*
 * NumberLiteralColumnParam.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_select/scan_columns/scan_columns_params/NumberLiteralColumnParam.h"

#include "base/UnicodeString.h"
#include "base/Long.h"

namespace codablecash {

NumberLiteralColumnParam::NumberLiteralColumnParam(int64_t longv) {
	this->longv = longv;
}

NumberLiteralColumnParam::~NumberLiteralColumnParam() {

}

const UnicodeString* NumberLiteralColumnParam::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = Long::toString(this->longv, 10);
	}

	return this->str;
}

} /* namespace codablecash */
