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
	this->length = 0;
}

ColumnIndexMatcher::~ColumnIndexMatcher() {
	this->idx = nullptr;
}

void ColumnIndexMatcher::doMatch(const ArrayList<CdbOid>* oidlist) noexcept {
}

} /* namespace codablecash */
