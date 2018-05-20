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

	this->includedPos = -1;
	this->lowerPos = -1;
	this->higherPos = -1;

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

LongRange* LongRangeHitStatus::getLow() const noexcept {
	return this->included == nullptr ? this->lower : this->included;
}

LongRange* LongRangeHitStatus::getHigh() const noexcept {
	return this->included == nullptr ? this->higher : this->included;
}

} /* namespace alinous */


