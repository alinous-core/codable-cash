/*
 * LongRange.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/LongRange.h"

#include "debug/debugMacros.h"

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
/*
uint64_t LongRange::width() noexcept {
	return this->min - this->max + 1;
}
*/
bool LongRange::hasNext(uint64_t value) const noexcept {
	return this->max > value;
}

uint64_t LongRange::getMin() const noexcept {
	return this->min;
}

void LongRange::setMin(uint64_t min) noexcept {
	this->min = min;
	assert(this->min <= this->max);
}

uint64_t LongRange::getMax() const noexcept {
	return this->max;
}

void LongRange::setMax(uint64_t max) noexcept {
	this->max = max;
	assert(this->min <= this->max);
}

int LongRange::compare(uint64_t value) const noexcept {
	if(min <= value && value <= max){
		return 0;
	}

	if(min > value){
		return 1;
	}
	return -1;
}

bool LongRange::removeLow(uint64_t value) noexcept {
	assert(this->min <= value);

	//if(this->min == this->max && this->min){
	//	return true;
	//}

	this->min = value + 1;
	return !(this->min <= this->max);
}

bool LongRange::removeHigh(uint64_t value) noexcept {
	assert(this->max >= value);

	//if(this->min == this->max && this->min){
	//	return true;
	//}

	this->max = value - 1;
	return !(this->min <= this->max);
}

} /* namespace alinous */


