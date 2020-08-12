/*
 * MemoryNodeCursor.cpp
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#include "btree_memory/MemoryNodeCursor.h"
#include "btree_memory/MemoryNodeHandle.h"
#include "btree_memory/MemoryDataNode.h"

#include "btree/AbstractBtreeKey.h"

#include "filestore_block/IBlockObject.h"

namespace alinous {

MemoryNodeCursor::MemoryNodeCursor(MemoryNodeHandle* rootNode, int nodeNumber) {
	this->nodestack = new ArrayList<MemoryNodeHandle>();
	this->nodeNumber = nodeNumber;

	push(rootNode);
}

MemoryNodeCursor::~MemoryNodeCursor() {
	int maxLoop = this->nodestack->size();
	for(int i = 0; i != maxLoop; ++i){
		MemoryNodeHandle* n = this->nodestack->get(i);
		delete n;
	}
}

void MemoryNodeCursor::insert(const AbstractBtreeKey* key, IBlockObject* data) {
	MemoryNodeHandle* current = top();

	while(!current->isLeaf()){
		current = current->getNextChild(key);
		push(current);
	}

	// 1. already has key
	AbstractMemoryTreeNode* node = current->hasKey(key);
	if(node != nullptr){
		MemoryDataNode* dnode = dynamic_cast<MemoryDataNode*>(node);
		dnode->setData(data);
		return;
	}

	// 2. Add key, then check whether the node is full or not
	if(current->isFull(this->nodeNumber)){
		// FIXME split node
		return;
	}


	// simply add data
	MemoryDataNode* dnode = new MemoryDataNode(key->clone());
	current->addData(dnode);
}

MemoryNodeHandle* MemoryNodeCursor::pop() noexcept {
	int index = this->nodestack->size() - 1;
	MemoryNodeHandle* node = this->nodestack->get(index);

	this->nodestack->remove(index);

	return node;
}

void MemoryNodeCursor::push(MemoryNodeHandle* node) noexcept {
	this->nodestack->addElement(node);
}

MemoryNodeHandle* MemoryNodeCursor::top() noexcept {
	int index = this->nodestack->size() - 1;
	return this->nodestack->get(index);
}

} /* namespace alinous */
