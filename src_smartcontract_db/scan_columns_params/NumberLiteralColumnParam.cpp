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

const UnicodeString* NumberLiteralColumnParam::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
