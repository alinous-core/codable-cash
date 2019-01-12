/*
 * NodeHandle.cpp
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#include "btree/NodeHandle.h"
#include "btree/NodeCacheRef.h"
#include "btree/TreeNode.h"
#include "btree/DataNode.h"

namespace alinous {

NodeHandle::NodeHandle(NodeCacheRef* ref) {
	this->ref = ref;
	ref->inc();
}

NodeHandle::~NodeHandle() {
	ref->dec();
}

NodeHandle* NodeHandle::clone() const noexcept {
	NodeHandle* newInst = new NodeHandle(this->ref);
	return newInst;
}

bool NodeHandle::isRoot() const {
	return AbstractTreeNode::toTreeNode(this->ref->getNode())->isRoot();
}

void NodeHandle::setIsRoot(bool isroot) {
	return AbstractTreeNode::toTreeNode(this->ref->getNode())->setIsRoot(isroot);
}

bool NodeHandle::isLeaf() const {
	return AbstractTreeNode::toTreeNode(this->ref->getNode())->isLeaf();
}

bool NodeHandle::isData() const noexcept {
	return this->ref->getNode()->isData();
}

NodeCacheRef* NodeHandle::getRef() const noexcept {
	return this->ref;
}

TreeNode* NodeHandle::toTreeNode() const {
	return AbstractTreeNode::toTreeNode(this->ref->getNode());
}

DataNode* NodeHandle::toDataNode() const {
	return AbstractTreeNode::toDataNode(this->ref->getNode());
}

RawArrayPrimitive<uint64_t>* NodeHandle::getInnerNodeFpos() const {
	TreeNode* treeNode = toTreeNode();

	return treeNode->getInnerNodeFpos();
}

AbstractBtreeKey* NodeHandle::getKey() const noexcept {
	return this->ref->getNode()->getKey();
}

uint64_t NodeHandle::getFpos() const noexcept {
	return  this->ref->getNode()->getFpos();
}

} /* namespace alinous */
