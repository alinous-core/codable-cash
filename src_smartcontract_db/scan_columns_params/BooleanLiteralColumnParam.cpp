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

const UnicodeString* BooleanLiteralColumnParam::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
