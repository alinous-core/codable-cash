/*
 * LongRangeHitStatus.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/LongRangeHitStatus.h"

#include "filestore/LongRange.h"
namespace alinous {

LongRangeHitStatus::LongRangeHitStatus(const LongRange* range) noexcept {
	this->current = new LongRange(range);
	this->included = nullptr;
	this->lower = nullptr;
	this->higher = nullptr;

}

LongRangeHitStatus::~LongRangeHitStatus() {
	delete this->current;
}

bool LongRangeHitStatus::lowJoinable() const noexcept {
	return (this->lower != nullptr && this->lower->getMax() + 1 == this->current->getMin() ) ||
			( this->included != nullptr );
}

bool LongRangeHitStatus::highJoinable() const noexcept {
	return (this->higher != nullptr && this->higher->getMin() - 1 == this->current->getMax()) ||
			( this->included != nullptr );
}

} /* namespace alinous */


