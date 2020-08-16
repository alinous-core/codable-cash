/*
 * ColumnIndexMatcher.cpp
 *
 *  Created on: 2020/08/16
 *      Author: iizuka
 */

#include "table/ColumnIndexMatcher.h"

namespace codablecash {

ColumnIndexMatcher::ColumnIndexMatcher(CdbTableIndex* idx) {
	this->idx = idx;
}

ColumnIndexMatcher::~ColumnIndexMatcher() {
	this->idx = nullptr;
}

} /* namespace codablecash */
