/*
 * MemoryNodeHandle.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/MemoryNodeHandle.h"

namespace alinous {

MemoryNodeHandle::MemoryNodeHandle(AbstractTreeNode* node) {
	this->node = node;
}

MemoryNodeHandle::~MemoryNodeHandle() {
	this->node = nullptr;
}

} /* namespace alinous */
