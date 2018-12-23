/*
 * TreeNode.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/TreeNode.h"
#include "btree/AbstractBtreeKey.h"
#include "base_io/ReverseByteBuffer.h"

namespace alinous {

TreeNode::TreeNode(int numChildren, AbstractBtreeKey* key) : AbstractTreeNode(key) {
	this->root = false;
	this->children = new ArrayList<AbstractTreeNode>(numChildren);
	for(int i = 0; i != numChildren; ++i){
		this->children->addElement(nullptr);
	}
}

TreeNode::TreeNode(bool isroot, int numChildren, AbstractBtreeKey* key) : AbstractTreeNode(key) {
	this->root = isroot;
	this->children = new ArrayList<AbstractTreeNode>(numChildren);
	for(int i = 0; i != numChildren; ++i){
		this->children->addElement(nullptr);
	}
}

TreeNode::~TreeNode() {
	delete this->children, this->children = nullptr;
}

bool TreeNode::isRoot() const noexcept {
	return this->root;
}

int TreeNode::binarySize() {
	int size = sizeof(char); // nodetype

	size += AbstractTreeNode::binarySize(); // key + fpos...

	size += sizeof(int); // number of children
	size += sizeof(uint64_t) * this->children->size();

	return size;
}

void TreeNode::toBinary(ByteBuffer* out) {
	out->put(AbstractTreeNode::NODE); // nodetype

	AbstractTreeNode::toBinary(out); // key + fpos...

	int maxLoop = this->children->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractTreeNode* node = this->children->get(i);

		uint64_t fpos = (node == nullptr) ? 0 : node->getFpos();
		out->putLong(fpos);
	}
}

} /* namespace alinous */
