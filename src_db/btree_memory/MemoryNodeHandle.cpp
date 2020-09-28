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
	this->pos = 0;
}

MemoryNodeHandle::~MemoryNodeHandle() {
	this->node = nullptr;
}

bool MemoryNodeHandle::isLeaf() const noexcept {
	return dynamic_cast<MemoryTreeNode*>(this->node)->isLeaf();
}

bool MemoryNodeHandle::isRoot() const noexcept {
	return dynamic_cast<MemoryTreeNode*>(this->node)->isRoot();
}

void MemoryNodeHandle::setRoot(bool isroot) noexcept {
	dynamic_cast<MemoryTreeNode*>(this->node)->setRoot(isroot);
}

MemoryNodeHandle* MemoryNodeHandle::getNextChild(const AbstractBtreeKey* key) {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	ArrayList<AbstractMemoryTreeNode>* list = node->getChildren();

	MemoryNodeHandle* ret = nullptr;
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractMemoryTreeNode* node = list->get(i);
		this->pos = i;

		if(key->compareTo(node->getKey()) <= 0){
			ret = new MemoryNodeHandle(node);
			break;
		}
	}

	// this->pos++; // not necessary, because always hit.
	return ret;
}

MemoryNodeHandle* MemoryNodeHandle::gotoEqMoreThanKey(const AbstractBtreeKey* key) {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	ArrayList<AbstractMemoryTreeNode>* list = node->getChildren();

	MemoryNodeHandle* ret = nullptr;

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		this->pos = i;
		AbstractMemoryTreeNode* n = list->get(i);
		if(key->compareTo(n->getKey()) <= 0){
			ret = new MemoryNodeHandle(n);
			break;
		}
	}

	// this->pos++; // not necessary, because always hit.
	return ret;
}

MemoryNodeHandle* alinous::MemoryNodeHandle::gotoEqKey(const AbstractBtreeKey* key) {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	ArrayList<AbstractMemoryTreeNode>* list = node->getChildren();

	MemoryNodeHandle* ret = nullptr;

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		this->pos = i;
		AbstractMemoryTreeNode* n = list->get(i);
		if(key->compareTo(n->getKey()) == 0){
			ret = new MemoryNodeHandle(n);
			break;
		}
	}

	// this->pos++; // not necessary, because always hit.
	return ret;
}


bool MemoryNodeHandle::hasNext() const noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	ArrayList<AbstractMemoryTreeNode>* list = node->getChildren();

	return list->size() > this->pos;
}

AbstractMemoryTreeNode* MemoryNodeHandle::nextNode() noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	ArrayList<AbstractMemoryTreeNode>* list = node->getChildren();

	if(list->size() - 1 < this->pos){
		return nullptr;
	}

	return list->get(this->pos++);
}

AbstractMemoryTreeNode* MemoryNodeHandle::hasKey(const AbstractBtreeKey* key) const noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	ArrayList<AbstractMemoryTreeNode>* list = node->getChildren();

	AbstractMemoryTreeNode* ret = nullptr;

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractMemoryTreeNode* node = list->get(i);

		if(key->compareTo(node->getKey()) == 0){
			ret = node;
			break;
		}
	}

	return ret;
}

const AbstractBtreeKey* MemoryNodeHandle::getKey() const noexcept {
	return this->node->getKey();
}

bool MemoryNodeHandle::isFull(int nodeNumber) const noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	return node->isFull(nodeNumber);
}

void MemoryNodeHandle::addNode(AbstractMemoryTreeNode* anode) noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	node->addNode(anode);
}

ArrayList<AbstractMemoryTreeNode>* MemoryNodeHandle::getInnerNodes() const noexcept {
	MemoryTreeNode* node = dynamic_cast<MemoryTreeNode*>(this->node);
	return node->getChildren();
}

void MemoryNodeHandle::updateInnerNodes(const ArrayList<AbstractMemoryTreeNode>* list) noexcept {
	dynamic_cast<MemoryTreeNode*>(this->node)->updateInnerNodes(list);
}


} /* namespace alinous */
