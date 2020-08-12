/*
 * MemoryNodeHandle.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/MemoryNodeHandle.h"
#include "btree_memory/MemoryTreeNode.h"

namespace alinous {

MemoryNodeHandle::MemoryNodeHandle(AbstractTreeNode* node) {
	this->node = node;
}

MemoryNodeHandle::~MemoryNodeHandle() {
	this->node = nullptr;
}

bool MemoryNodeHandle::isLeaf() const noexcept {
	return dynamic_cast<MemoryTreeNode*>(this->node)->isLeaf();
}

MemoryNodeHandle* MemoryNodeHandle::getNextChild(const AbstractBtreeKey* key) {


	// FIXME getNextChild()
}

} /* namespace alinous */
