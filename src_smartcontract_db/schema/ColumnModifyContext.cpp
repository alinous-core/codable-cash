/*
 * ColumnModifyContext.cpp
 *
 *  Created on: 2020/09/19
 *      Author: iizuka
 */

#include "schema/ColumnModifyContext.h"

#include "base/UnicodeString.h"

namespace codablecash {

ColumnModifyContext::ColumnModifyContext() {
	this->uniqueChange = UniqueChage::UNIQUE_NONE;
	this->typeChanged = false;
	this->notNullChange = NotNullChage::NOTNULL_NONE;

	this->cdbType = 0;
	this->length = 0;
	this->defalutValueStr = nullptr;
}

ColumnModifyContext::~ColumnModifyContext() {
	delete this->defalutValueStr;
}


void ColumnModifyContext::setDefaultValue(const UnicodeString* defalutValueStr) noexcept {
	this->defalutValueStr = defalutValueStr != nullptr ? new UnicodeString(defalutValueStr) : nullptr;
}

} /* namespace codablecash */
