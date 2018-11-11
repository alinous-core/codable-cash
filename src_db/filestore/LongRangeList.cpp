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

#include "base_io/ByteBuffer.h"

namespace alinous {


LongRangeList::LongRangeList() {
	this->list = new ArrayList<LongRange>();
}

LongRangeList::~LongRangeList() {
	this->list->deleteElements();
	delete this->list;
}

void LongRangeList::removeRange(int64_t min, int64_t max) noexcept {
	assert(min <= max);

	LongRange range(min, max);
	removeRange(&range);
}

void LongRangeList::removeRange(const LongRange* range) noexcept {
	_ST(LongRangeHitStatus, minStatus, hitStatus(range->getMin(), range, false))
	_ST(LongRangeHitStatus, maxStatus, hitStatus(range->getMax(), range, true))

	// check inclusion
	removeInclusion(range);

	// split
	if(needSplit(minStatus, maxStatus, range)){
		return;
	}

	// no split
	if(minStatus->hasIncluded()){
		LongRange* r = minStatus->getIncluded();
		bool remove = r->removeHigh(range->getMin());

		if(remove){
			int idx = this->list->indexOfPtr(r);
			this->list->remove(idx);
			delete r;
		}
	}
	if(maxStatus->hasIncluded()){
		LongRange* r = maxStatus->getIncluded();
		bool remove = r->removeLow(range->getMax());
		if(remove){
			int idx = this->list->indexOfPtr(r);
			this->list->remove(idx);
			delete r;
		}
	}

}


bool LongRangeList::needSplit(LongRangeHitStatus* minStatus, LongRangeHitStatus* maxStatus, const LongRange* range) noexcept {
	LongRange* minRange = minStatus->getIncluded();
	LongRange* maxRange = maxStatus->getIncluded();

	if((minRange != nullptr && maxRange != nullptr && minRange != maxRange) ||
			(minRange == nullptr && maxRange == nullptr)){
		return false;
	}

	uint64_t highRangeStart = range->getMax();
	uint64_t lowRangeStart = range->getMin();

	bool lowExists = minRange->getMin() < lowRangeStart;
	bool highExists = minRange->getMax() > highRangeStart;

	if(lowExists && highExists){
		uint64_t low = minRange->getMin();
		uint64_t high = lowRangeStart - 1;

		LongRange* newRange = new LongRange(low, high);

		minRange->setMin(highRangeStart + 1);

		insertRange(minStatus->includedPos, newRange);
	}
	else if(!lowExists && highExists){
		minRange->setMin(highRangeStart + 1);
	}
	else if(lowExists && !highExists){
		minRange->setMax(lowRangeStart - 1);
	}
	else{
		LongRange* r = this->list->get(minStatus->includedPos);
		this->list->remove(minStatus->includedPos);
		delete r;
	}

	return true;
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

	// check
	LongRange* range = new LongRange(min, max);
	_ST(LongRangeHitStatus, minStatus, hitStatus(range->getMin(), range, false))
	_ST(LongRangeHitStatus, maxStatus, hitStatus(range->getMax(), range, true))

	// check inclusion
	removeInclusion(range);

	if(minStatus->lowJoinable() && maxStatus->highJoinable()){
		int removePos = maxStatus->getHighPos();
		LongRange* rangeHigh = maxStatus->getHigh();
		LongRange* rangeLow = minStatus->getLow();

		rangeLow->setMin(rangeLow->getMin() < range->getMin() ? rangeLow->getMin() : range->getMin());
		rangeLow->setMax(rangeHigh->getMax() > range->getMax() ? rangeHigh->getMax() : range->getMax());

		if(rangeHigh != rangeLow){
			list->remove(removePos);
			delete rangeHigh;
		}

		delete range;
	}
	else if(!minStatus->lowJoinable() && maxStatus->highJoinable()){
		LongRange* range2update = maxStatus->getHigh(); // high from range
		assert(range2update != nullptr);

		range2update->setMin(range->getMin());
		delete range;
	}
	else if(minStatus->lowJoinable() && !maxStatus->highJoinable()){
		LongRange* range2update = minStatus->getLow(); // low from range
		assert(range2update != nullptr);

		range2update->setMax(range->getMax());

		delete range;
	}
	else { // if(!minStatus->lowJoinable() && !maxStatus->highJoinable()){
		int insertPos = minStatus->lower != nullptr ? minStatus->lowerPos + 1 : 0;
		insertRange(insertPos, range);
	}
}

void LongRangeList::removeInclusion(const LongRange* range) const noexcept {
	_ST(LongRangeHitStatus, minStatus, hitStatus(range->getMin(), range, true))
	_ST(LongRangeHitStatus, maxStatus, hitStatus(range->getMax(), range, false))

	int minPos = minStatus->getHigherIncludePos(this->list->size());
	int maxPos = maxStatus->getLowerIncludePos(); // getHighPos(this->list->size()) - 1;

	int length = maxPos - minPos + 1;
	for(int i = 0; i < length; ++i){
		LongRange* r = this->list->remove(minPos);
		delete r;
	}
}


void LongRangeList::insertRange(int pos, LongRange* range) noexcept {
	int lastSize = list->size();

	list->addElement(nullptr);

	for(int i = lastSize; i != pos; --i){
		LongRange* r = list->get(i - 1);
		list->setElement(r, i);
	}

	list->setElement(range, pos);
}


LongRangeHitStatus* LongRangeList::hitStatus(uint64_t value, const LongRange* range, bool findHigher) const noexcept {
	LongRangeHitStatus* status = new LongRangeHitStatus(range);

	int begin = 0;
	int end = this->list->size() - 1;

	int minIndex;
	LongRange* midRange = nullptr;

	int mid = -1;
	do{
		mid = (begin + end) / 2;

		midRange = list->get(mid);
		int cmp = midRange->compare(value);

		if(cmp < 0){
			begin = mid + 1;
		}
		else if(cmp > 0){
			end = mid - 1;
		}
		else { // cmp == 0
			status->included = midRange;
			status->includedPos = mid;
			return status;
		}
	}while(begin <= end);

	// find nearest
	if(findHigher){
		int listSize = this->list->size();
		while(mid < listSize){
			midRange = this->list->get(mid);
			if(midRange->compare(value) > 0){
				status->higher = midRange;
				status->higherPos = mid;
				break;
			}
			mid++;
		}
	}
	else{ // lower range
		while(mid >= 0){
			midRange = this->list->get(mid);
			if(midRange->compare(value) < 0){
				status->lower = midRange;
				status->lowerPos = mid;
				break;
			}
			mid--;
		}
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


void LongRangeList::assertList() const {
	LongRange* lastRange = nullptr;

	int maxLoop = this->list->size();
	for(int i = 0; i != maxLoop; ++i){
		LongRange* range = this->list->get(i);

		if(lastRange == nullptr){
			lastRange = range;
			continue;
		}

		uint64_t rangeMin = range->getMin();
		uint64_t rangeMax = lastRange->getMax();

		assert(rangeMax < rangeMin);
		lastRange = range;
	}
}

int LongRangeList::binarySize() noexcept {
	int size = 4;

	int maxLoop = this->list->size();
	for(int i = 0; i != maxLoop; ++i){
		LongRange* range = this->list->get(i);
		size += range->binarySize();
	}

	return size;
}

void LongRangeList::toBinary(ByteBuffer* buff) noexcept {
	int size = this->size();
	buff->putInt(size);

	for(int i = 0; i != size; ++i){
		LongRange* range = this->list->get(i);
		range->toBinary(buff);
	}
}

LongRangeList* LongRangeList::fromBinary(ByteBuffer* buff) noexcept {
	LongRangeList* list = new LongRangeList();

	int size = buff->getInt();

	for(int i = 0; i != size; ++i){
		LongRange* range = LongRange::fromBinary(buff);

		list->addRange(range->getMin(), range->getMax());
		delete range;
	}

	return list;
}

bool LongRangeList::equals(LongRangeList* other) noexcept {
	int maxLoop = other->size();
	if(maxLoop != size()){
		return false;
	}

	for(int i = 0; i != maxLoop; ++i){
		LongRange* range = this->list->get(i);
		LongRange* range2 = other->get(i);

		if(!range->equals(range2)){
			return false;
		}
	}
	return true;
}



} /* namespace alinous */

