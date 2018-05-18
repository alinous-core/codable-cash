/*
 * LongRange.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/LongRange.h"

namespace alinous {


LongRange::LongRange(const LongRange* base) noexcept {
	this->min = base->min;
	this->max = base->max;
}

LongRange::LongRange(uint64_t min, uint64_t max) noexcept {
	this->min = min;
	this->max = max;
}

LongRange::~LongRange() {
}

uint64_t LongRange::width() noexcept {
	return this->min - this->max + 1;
}

bool LongRange::hasNext(uint64_t value) const noexcept {
	return this->max > value;
}

uint64_t LongRange::getMin() const noexcept {
	return this->min;
}

void LongRange::setMin(uint64_t min) noexcept {
	this->min = min;
}

uint64_t LongRange::getMax() const noexcept {
	return this->max;
}

int LongRange::compare(uint64_t value) const noexcept {
	if(min > value){
		return 1;
	}
	if(max < value){
		return -1;
	}

	return 0;
}

void LongRange::setMax(uint64_t max) noexcept {
	this->max = max;
}

} /* namespace alinous */


