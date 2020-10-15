/*
 * AbstractCdbValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "schema_table/record/table_record_value/AbstractCdbValue.h"

namespace codablecash {

AbstractCdbValue::AbstractCdbValue(uint8_t type) {
	this->type = type;
}

AbstractCdbValue::~AbstractCdbValue() {

}

IBlockObject* codablecash::AbstractCdbValue::copyData() const noexcept {
	return copy();
}


} /* namespace codablecash */
