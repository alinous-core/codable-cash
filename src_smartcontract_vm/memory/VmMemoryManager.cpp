/*
 * VmMemoryManager.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "memory/VmMemoryManager.h"
#include "filestore/LongRangeList.h"
#include "filestore/LongRange.h"

#include "base/StackRelease.h"

#include "vm/exceptions.h"

namespace alinous {

VmMemoryManager::VmMemoryManager(uint64_t capacity) {
	this->mem = new char[capacity]{};

	this->used = new LongRangeList();
	this->available = new LongRangeList();
	this->available->addRange(0, capacity - 1);

	this->capacity = capacity;
	this->capacityUsed = 0;
}

VmMemoryManager::~VmMemoryManager() {
	delete this->used;
	delete this->available;
	delete [] this->mem;
}

char* VmMemoryManager::malloc(uint32_t cap) {
	uint64_t remain =this->capacity - this->capacityUsed;
	if(remain < cap){
		throw new VmMemoryAllocationException(__FILE__, __LINE__);
	}

	int64_t start = -1;
	uint32_t allocSize = cap + sizeof(uint32_t);

	int maxLoop = this->available->size();
	for(int i = 0; i != maxLoop; ++i){
		LongRange* range = this->available->get(i);

		if(range->width() >= allocSize){
			start = range->getMin();
			break;
		}
	}

	int64_t end = start + allocSize - 1;
	this->available->removeRange(start, end);
	this->used->addRange(start, end);

	char* ptr = this->mem + start;

	uint32_t* head = (uint32_t*)ptr;
	*head = allocSize;

	this->capacityUsed += allocSize;


	return ptr + sizeof(uint32_t);
}

void VmMemoryManager::free(char* ptr) {
	uint32_t allocSize = getSize(ptr);
	int64_t start = ptr - this->mem - sizeof(uint32_t);
	int64_t end = start + allocSize - 1;



	this->available->addRange(start, end);
	this->used->removeRange(start, end);
	this->capacityUsed -= allocSize;
}

uint32_t VmMemoryManager::getSize(char* ptr) const noexcept {
	char* head = ptr - sizeof(uint32_t);


	return *head;
}

} /* namespace alinous */
