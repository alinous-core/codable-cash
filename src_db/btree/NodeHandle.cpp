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

bool NodeHandle::isRoot() const {
	return AbstractTreeNode::toTreeNode(this->ref->getNode())->isRoot();
}

bool NodeHandle::isLeaf() const {
	return AbstractTreeNode::toTreeNode(this->ref->getNode())->isLeaf();
}

bool NodeHandle::isData() const noexcept {
	return this->ref->getNode()->isData();
}

TreeNode* NodeHandle::toTreeNode() const {
	return AbstractTreeNode::toTreeNode(this->ref->getNode());
}

DataNode* NodeHandle::toDataNode() const {
	return AbstractTreeNode::toDataNode(this->ref->getNode());
}

} /* namespace alinous */
