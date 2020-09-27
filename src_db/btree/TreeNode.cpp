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

TreeNode::TreeNode(const TreeNode& inst) : AbstractTreeNode(inst.key->clone()) {
	this->fpos = inst.fpos;

	this->root = inst.root;
	this->leaf = inst.leaf;

	this->children = new RawArrayPrimitive<uint64_t>(inst.children->size());

	int maxLoop = inst.children->size();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t v = inst.children->get(i);
		this->children->addElement(v);
	}
}

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

void TreeNode::setIsRoot(bool isroot) noexcept {
	this->root = isroot;
}

int TreeNode::binarySize() const {
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

void TreeNode::toBinary(ByteBuffer* out) const {
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

TreeNode* TreeNode::fromBinary(ByteBuffer* in, BtreeKeyFactory* factory) {
	TreeNode* node = new TreeNode();

	node->fromBinaryAbstract(in, factory);

	node->root = (in->get() == 1);
	node->leaf = (in->get() == 1);

	int maxLoop = in->getInt();
	node->children = new RawArrayPrimitive<uint64_t>(maxLoop);

	int i = 0;
	for(; i != maxLoop; ++i){
		uint64_t nodefpos = in->getLong();
		node->children->addElement(nodefpos);
	}

	return node;
}

RawArrayPrimitive<uint64_t>* TreeNode::getInnerNodeFpos() const {
	return this->children;
}

void TreeNode::updateInnerNodeFpos(const RawArrayPrimitive<uint64_t>* newlist) noexcept {
	int maxLoop = this->children->size();
	for(int i = 0; i != maxLoop; ++i){
		this->children->set(i, 0);
	}

	maxLoop = newlist->size();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t f = newlist->get(i);
		this->children->set(i, f);
	}
}

IBlockObject* TreeNode::copyData() const noexcept {
	return new TreeNode(*this);
}

} /* namespace alinous */
