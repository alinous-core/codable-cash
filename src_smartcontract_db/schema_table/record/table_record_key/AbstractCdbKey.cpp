/*
 * AbstractCdbKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "schema_table/record/table_record_key/AbstractCdbKey.h"

namespace codablecash {

AbstractCdbKey::AbstractCdbKey(uint32_t type) {
	this->type = type;
}

AbstractCdbKey::~AbstractCdbKey() {

}

bool AbstractCdbKey::isInfinity() const {
	return false;
}

bool AbstractCdbKey::isNull() const {
	return false;
}

} /* namespace codablecash */
