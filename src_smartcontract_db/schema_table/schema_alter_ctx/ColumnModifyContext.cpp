/*
 * ColumnModifyContext.cpp
 *
 *  Created on: 2020/09/19
 *      Author: iizuka
 */

#include "schema_table/schema_alter_ctx/ColumnModifyContext.h"

#include "base/UnicodeString.h"

#include "schema_table/table/CdbTableIndex.h"
#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"

#include "schema_table/record/table_record_value/CdbValueCaster.h"

namespace codablecash {

ColumnModifyContext::ColumnModifyContext() {
	this->uniqueChange = UniqueChage::UNIQUE_NONE;
	this->typeChanged = false;
	this->notNullChange = NotNullChage::NOTNULL_NONE;
	this->lengthChange = LengthChange::LENGTH_NO_CHANGE;

	this->notNull = false;
	this->unique = false;

	this->cdbType = 0;
	this->length = 0;
	this->defalutValueStr = nullptr;

	this->column = nullptr;
	this->newIndex = nullptr;
	this->removalIndex = nullptr;

	this->defaultChanged = false;

	this->defaultValue = nullptr;
}

ColumnModifyContext::~ColumnModifyContext() {
	delete this->defalutValueStr;

	this->column = nullptr;
	this->newIndex = nullptr;
	delete this->removalIndex;

	delete this->defaultValue;
}

void ColumnModifyContext::analyze() {
	analyzeDefaultValue();
}

void ColumnModifyContext::analyzeDefaultValue() {
	this->defaultValue = CdbValueCaster::convertFromString(this->defalutValueStr, this->cdbType);
}

void ColumnModifyContext::setDefaultValue(const UnicodeString* defalutValueStr) noexcept {
	this->defalutValueStr = defalutValueStr != nullptr ? new UnicodeString(defalutValueStr) : nullptr;
}

} /* namespace codablecash */
