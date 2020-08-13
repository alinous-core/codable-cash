/*
 * MemoryTreeNode.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/MemoryTreeNode.h"
#include "btree_memory/MemoryDataNode.h"
#include "btree_memory/AbstractMemoryTreeNode.h"

#include "btree/AbstractTreeNode.h"

#include "btree/AbstractBtreeKey.h"

namespace alinous {

MemoryTreeNode::MemoryTreeNode(int numChildren, AbstractBtreeKey* key, bool leaf) : AbstractMemoryTreeNode(key) {
	this->root = false;
	this->leaf = leaf;
	this->children = new ArrayList<AbstractMemoryTreeNode>(numChildren);
}

MemoryTreeNode::MemoryTreeNode(bool isroot, int numChildren, AbstractBtreeKey* key, bool leaf) : AbstractMemoryTreeNode(key) {
	this->root = isroot;
	this->leaf = leaf;
	this->children = new ArrayList<AbstractMemoryTreeNode>(numChildren);
}

MemoryTreeNode::~MemoryTreeNode() {
	this->children->deleteElements();
	delete this->children;
}

bool MemoryTreeNode::isData() const noexcept {
	return false;
}

bool MemoryTreeNode::isLeaf() const noexcept {
	return this->leaf;
}

bool MemoryTreeNode::isFull(int nodeNumber) const noexcept {
	return this->children->size() >= nodeNumber;
}

void MemoryTreeNode::addNode(AbstractMemoryTreeNode* dnode) noexcept {
	AbstractBtreeKey* newKey = dnode->getKey();

	int maxLoop = this->children->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractMemoryTreeNode* n = this->children->get(i);

		if(n->getKey()->compareTo(newKey) > 0){
			internalAddNode(i, dnode);
			return;
		}
	}

	this->children->addElement(dnode);
}

void alinous::MemoryTreeNode::internalAddNode(int index, AbstractMemoryTreeNode* node) noexcept {
	this->children->addElement(nullptr);

	int first = this->children->size() - 1;
	for(int i = first; i > index; --i){
		AbstractMemoryTreeNode* f = this->children->get(i - 1);
		this->children->setElement(f, i);
	}
	this->children->setElement(node, index);
}

void MemoryTreeNode::updateInnerNodes(const ArrayList<AbstractMemoryTreeNode>* list) noexcept {
	this->children->reset();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractMemoryTreeNode* node = list->get(i);
		this->children->addElement(node);
	}
}


} /* namespace alinous */
