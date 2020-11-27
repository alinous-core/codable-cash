/*
 * SingleColumnIndex.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/SingleColumnIndex.h"

namespace codablecash {

SingleColumnIndex::SingleColumnIndex() {
	this->column = nullptr;
}

SingleColumnIndex::~SingleColumnIndex() {
	this->column = nullptr;
}

int SingleColumnIndex::size() const noexcept {
	return 1;
}

} /* namespace codablecash */
