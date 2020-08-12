/*
 * MemoryTreeNode.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/MemoryTreeNode.h"

#include "btree/AbstractTreeNode.h"
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


} /* namespace alinous */
