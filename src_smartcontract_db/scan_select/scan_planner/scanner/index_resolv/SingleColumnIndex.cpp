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

	this->topEq = false;
	this->topValue = nullptr;
	this->bottomEq = false;
	this->value = nullptr;

	this->range = false;
}

SingleColumnIndex::~SingleColumnIndex() {
	this->column = nullptr;
	this->topValue = nullptr;
	this->value = nullptr;
}

int SingleColumnIndex::size() const noexcept {
	return 1;
}

bool SingleColumnIndex::isRange() const noexcept {
	return this->range;
}

void SingleColumnIndex::setRange(bool range) noexcept {
	this->range = range;
}

} /* namespace codablecash */
