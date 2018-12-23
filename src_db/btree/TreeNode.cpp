/*
 * TreeNode.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/TreeNode.h"

namespace alinous {

TreeNode::TreeNode(int numChildren) : AbstractTreeNode() {
	this->root = false;
	this->children = new ArrayList<AbstractTreeNode>(numChildren);
}

TreeNode::TreeNode(bool isroot, int numChildren) : AbstractTreeNode() {
	this->root = isroot;
	this->children = new ArrayList<AbstractTreeNode>(numChildren);
}

TreeNode::~TreeNode() {
	delete this->children, this->children = nullptr;
}

bool TreeNode::isRoot() const noexcept {
	return this->root;
}

int TreeNode::binarySize() {
	int size = sizeof(int); // nodetype

	size += sizeof(char); // number of children
	size += sizeof(uint64_t) * this->children->size();

	return size;
}

void TreeNode::toBinary(ByteBuffer* out) {
	// TODO Auto-generated constructor stub
}

} /* namespace alinous */
