/*
 * LongRangeList.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/LongRangeList.h"
#include "filestore/LongRange.h"

namespace alinous {

LongRangeList::LongRangeList() {
	this->list = new ArrayList<LongRange>();
}

LongRangeList::~LongRangeList() {
	this->list->deleteElements();
	delete this->list;
}

void LongRangeList::addRange(int64_t value) noexcept {
	if(this->list->isEmpty()) {
		LongRange* newRange = new LongRange(value, value);
		list->addElement(newRange);
		return;
	}

}

int LongRangeList::indexOfInsert(int64_t value) const noexcept {
	int begin = 0;
	int end = this->list->size() - 1;
	int mid = (begin + end) / 2;
	while(begin <= end)	{
		mid = (begin + end) / 2;
		if(list->get(mid)->getMax() - value == (int64_t)0){
			return mid;
		}
		else {
			if(list->get(mid)->getMax() - value < (int64_t)0){
				begin = mid + 1;
			}
			else{
				end = mid - 1;
			}
		}
	}
	if(end < 0)	{
		return 0;
	}
	if(list->get(end)->getMax() - value > (int64_t)0) {
		return end;
	}
	if(begin >= this->list->size())	{
		return this->list->size();
	}
	if(list->get(begin)->getMax() - value > (int64_t)0){
		return begin;
	}
	return this->list->size();
}

} /* namespace alinous */
