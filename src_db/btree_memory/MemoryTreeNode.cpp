/*
 * MemoryTreeNode.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/MemoryTreeNode.h"

#include "btree/AbstractTreeNode.h"
namespace alinous {

MemoryTreeNode::MemoryTreeNode(int numChildren, AbstractBtreeKey* key, bool leaf) : AbstractTreeNode(key) {
	this->root = false;
	this->leaf = leaf;
	this->children = new ArrayList<AbstractTreeNode>(numChildren);
	for(int i = 0; i != numChildren; ++i){
		this->children->addElement(nullptr);
	}
}

MemoryTreeNode::MemoryTreeNode(bool isroot, int numChildren, AbstractBtreeKey* key, bool leaf) : AbstractTreeNode(key) {
	this->root = isroot;
	this->leaf = leaf;
	this->children = new ArrayList<AbstractTreeNode>(numChildren);
	for(int i = 0; i != numChildren; ++i){
		this->children->addElement(nullptr);
	}
}

MemoryTreeNode::~MemoryTreeNode() {
	this->children->deleteElements();
	delete this->children;
}

bool MemoryTreeNode::isData() const noexcept {
	return false;
}


} /* namespace alinous */
