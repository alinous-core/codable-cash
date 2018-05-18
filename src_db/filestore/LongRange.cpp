/*
 * LongRange.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/LongRange.h"

namespace alinous {

LongRange::LongRange(int64_t min, int64_t max) {
	this->min = min;
	this->max = max;
}

LongRange::~LongRange() {
}

int64_t LongRange::width() noexcept {
	return this->min - this->max + 1;
}

bool LongRange::hasNext(int64_t value) const noexcept {
	return this->max > value;
}

int64_t LongRange::getMin() const noexcept {
	return this->min;
}

void LongRange::setMin(int64_t min) noexcept {
	this->min = min;
}

int64_t LongRange::getMax() const noexcept {
	return this->max;
}

void LongRange::setMax(int64_t max) noexcept {
	this->max = max;
}

} /* namespace alinous */
