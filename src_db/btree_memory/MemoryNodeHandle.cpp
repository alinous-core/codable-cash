/*
 * MemoryNodeHandle.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/MemoryNodeHandle.h"
#include "btree_memory/MemoryTreeNode.h"

#include "btree_memory/AbstractMemoryTreeNode.h"

#include "base/ArrayList.h"

#include "btree/AbstractBtreeKey.h"

namespace alinous {

MemoryNodeHandle::MemoryNodeHandle(AbstractMemoryTreeNode* node) {
	this->node = node;
}

MemoryNodeHandle::~MemoryNodeHandle() {
	this->node = nullptr;
}

bool MemoryNodeHandle::isLeaf() const noexcept {
	return dynamic_cast<MemoryTreeNode*>(this->node)->isLeaf();
}

MemoryNodeHandle* MemoryNodeHandle::getNextChild(const AbstractBtreeKey* key) {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	ArrayList<AbstractMemoryTreeNode>* list = node->getChildren();

	MemoryNodeHandle* ret = nullptr;
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractMemoryTreeNode* node = list->get(i);

		if(key->compareTo(node->getKey()) <= 0){
			ret = new MemoryNodeHandle(node);
			break;
		}
	}

	return ret;
}

AbstractMemoryTreeNode* MemoryNodeHandle::hasKey(const AbstractBtreeKey* key) const noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	ArrayList<AbstractMemoryTreeNode>* list = node->getChildren();

	AbstractMemoryTreeNode* ret = nullptr;

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractMemoryTreeNode* node = list->get(i);

		if(key->compareTo(node->getKey()) <= 0){
			ret = node;
			break;
		}
	}

	return ret;
}

bool MemoryNodeHandle::isFull(int nodeNumber) const noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	return node->isFull(nodeNumber);
}

void MemoryNodeHandle::addNode(AbstractMemoryTreeNode* anode) noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	node->addNode(anode);
}

} /* namespace alinous */
