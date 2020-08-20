/*
 * StringLiteralColumnParam.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_params/StringLiteralColumnParam.h"

#include "base/UnicodeString.h"

namespace codablecash {

StringLiteralColumnParam::StringLiteralColumnParam(const UnicodeString* str) {
	this->value = new UnicodeString(str);
}

StringLiteralColumnParam::~StringLiteralColumnParam() {
	delete this->value;
}

} /* namespace codablecash */
