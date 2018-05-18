/*
 * LongRangeList.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/LongRangeList.h"
#include "filestore/LongRange.h"
#include "filestore/LongRangeIterator.h"
#include "filestore/LongRangeHitStatus.h"

#include "base/StackRelease.h"

namespace alinous {


LongRangeList::LongRangeList() {
	this->list = new ArrayList<LongRange>();
}

LongRangeList::~LongRangeList() {
	this->list->deleteElements();
	delete this->list;
}

void LongRangeList::addRange(int64_t value) noexcept {
	addRange(value, value);
}

void LongRangeList::addRange(int64_t min, int64_t max) noexcept {
	assert(min <= max);
	if(this->list->isEmpty()) {
		LongRange* newRange = new LongRange(min, max);
		list->addElement(newRange);
		return;
	}

	LongRange* range = new LongRange(min, max);
	_ST(LongRangeHitStatus, minStatus, hitStatus(range->getMin(), range, false))
	_ST(LongRangeHitStatus, maxStatus, hitStatus(range->getMax(), range, true))

}

LongRangeHitStatus* LongRangeList::hitStatus(uint64_t value, const LongRange* range, bool findHigher) const noexcept {
	LongRangeHitStatus* status = new LongRangeHitStatus(range);

	int begin = 0;
	int end = this->list->size() - 1;
	int mid = 0;

	int minIndex;
	LongRange* midRange = nullptr;

	do{
		mid = (begin + end) / 2;

		midRange = list->get(mid);
		int cmp = midRange->compare(value);
		if(cmp == 0){
			status->included = midRange;
			return status;
		}
		else if(cmp > 0){
			end = mid;
		}
		else{
			begin = mid;
		}
	}while(begin != end);

	// find nearest
	if(findHigher){
		do{
			midRange = this->list->get(begin);
			if(midRange->compare(value) > 0){
				status->higher = midRange;
				break;
			}
			begin++;
		}while(begin >= 0);
	}
	else{ // lower range
		do{
			midRange = this->list->get(begin);
			if(midRange->compare(value) < 0){
				status->lower = midRange;
				break;
			}
			begin--;
		}while(begin >= 0);
	}

	return status;
}

bool LongRangeList::isEmpty() const noexcept {
	return this->list->isEmpty();
}

int LongRangeList::size() const noexcept {
	return this->list->size();
}

LongRange* LongRangeList::get(int listIndex) const noexcept {
	return this->list->get(listIndex);
}

LongRangeIterator* LongRangeList::iterator() noexcept {
	return new LongRangeIterator(this);
}



} /* namespace alinous */
