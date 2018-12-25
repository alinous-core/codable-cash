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

TreeNode::TreeNode() : AbstractTreeNode(nullptr) {
	this->root = false;
	this->leaf = false;
	this->children = nullptr;
}

TreeNode::TreeNode(int numChildren, AbstractBtreeKey* key, bool leaf) : AbstractTreeNode(key) {
	this->root = false;
	this->leaf = leaf;
	this->children = new RawArrayPrimitive<uint64_t>(numChildren);
	for(int i = 0; i != numChildren; ++i){
		this->children->addElement(0);
	}
}

TreeNode::TreeNode(bool isroot, int numChildren, AbstractBtreeKey* key, bool leaf) : AbstractTreeNode(key) {
	this->root = isroot;
	this->leaf = leaf;
	this->children = new RawArrayPrimitive<uint64_t>(numChildren);
	for(int i = 0; i != numChildren; ++i){
		this->children->addElement(0);
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

	size += sizeof(char)*2; // isRoot + isLeaf

	size += sizeof(int32_t); // number of children
	size += sizeof(uint64_t) * this->children->size();

	return size;
}

bool TreeNode::isLeaf() const noexcept {
	return this->leaf;
}

void TreeNode::toBinary(ByteBuffer* out) {
	out->put(AbstractTreeNode::NODE); // nodetype

	AbstractTreeNode::toBinary(out); // key + fpos...

	out->put(this->root ? 1 : 0);
	out->put(this->leaf ? 1 : 0);

	int maxLoop = this->children->size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint64_t nodefpos = this->children->get(i);
		out->putLong(nodefpos);
	}
}

TreeNode* TreeNode::fromBinary(ByteBuffer* in, BTreeKeyFactory* factory) {
	TreeNode* node = new TreeNode();

	node->fromBinaryAbstract(in, factory);

	return node;
}


} /* namespace alinous */

