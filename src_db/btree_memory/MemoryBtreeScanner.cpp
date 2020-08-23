/*
 * MemoryBtreeScanner.cpp
 *
 *  Created on: 2020/08/13
 *      Author: iizuka
 */

#include "btree_memory/MemoryBtreeScanner.h"
#include "btree_memory/MemoryNodeCursor.h"

#include "btree/AbstractBtreeKey.h"

namespace alinous {

MemoryBtreeScanner::MemoryBtreeScanner(MemoryNodeCursor* cursor) {
	this->cursor = cursor;
	this->nextObj = nullptr;
	this->initialized = false;
	this->key = nullptr;
}

MemoryBtreeScanner::~MemoryBtreeScanner() {
	delete this->cursor;
	this->nextObj = nullptr;
	delete this->key;
}

void MemoryBtreeScanner::begin() {
	begin(nullptr);
}

void MemoryBtreeScanner::begin(const AbstractBtreeKey* key) {
	this->key = key != nullptr ? key->clone() : nullptr;
}

bool MemoryBtreeScanner::hasNext() {
	if(this->nextObj != nullptr){
		this->nextObj = nullptr;
	}

	if(!this->initialized){
		if(this->key == nullptr){
			this->nextObj = this->cursor->gotoFirst();
			this->initialized = true;
		}
		else{
			this->nextObj = this->cursor->gotoKey(this->key);
			this->initialized = true;
		}
	}
	else{
		this->nextObj = this->cursor->getNext();
	}

	return this->nextObj != nullptr;
}

const IBlockObject* MemoryBtreeScanner::next() {
	return this->nextObj;
}

const AbstractBtreeKey* MemoryBtreeScanner::nextKey() {
	return this->cursor->getCurrentKey();
}

} /* namespace alinous */
