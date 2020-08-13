/*
 * MemoryBtreeScanner.cpp
 *
 *  Created on: 2020/08/13
 *      Author: iizuka
 */

#include "btree_memory/MemoryBtreeScanner.h"
#include "btree_memory/MemoryNodeCursor.h"

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
}

} /* namespace alinous */
