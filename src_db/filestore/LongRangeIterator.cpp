/*
 * LongRangeIterator.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/LongRangeIterator.h"
#include "filestore/LongRangeList.h"
#include "filestore/LongRange.h"

namespace alinous {

LongRangeIterator::LongRangeIterator(LongRangeList* list) noexcept {
	this->list = list;

	this->listIndex = 0;
	if(this->list->isEmpty()){
		this->current = -1;
	}
	else{
		LongRange* range = list->get(this->listIndex);
		this->current = range->getMin();
	}
}

LongRangeIterator::~LongRangeIterator() noexcept {
}

bool LongRangeIterator::hasNext() noexcept {
	if(this->list->isEmpty() || listIndex == this->list->size())
	{
		return false;
	}
	return this->current > 0;
}

uint64_t LongRangeIterator::next() noexcept {
	long long ret = this->current;
	LongRange* range = list->get(this->listIndex);
	if(range->hasNext(this->current)){
		this->current ++ ;
	}
	else {
		if(list->size() - 1 > this->listIndex){
			this->listIndex ++ ;
			range = list->get(this->listIndex);
			this->current = range->getMin();
		}
		else {
			this->current = -1;
		}
	}
	return ret;
}

} /* namespace alinous */
