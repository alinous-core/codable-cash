/*
 * AbstractMemoryTreeNode.cpp
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#include "btree_memory/AbstractMemoryTreeNode.h"

#include "btree/AbstractBtreeKey.h"

namespace alinous {

AbstractMemoryTreeNode::AbstractMemoryTreeNode(AbstractBtreeKey* key) {
	this->key = key;
}

AbstractMemoryTreeNode::~AbstractMemoryTreeNode() {
	delete this->key;
}

} /* namespace alinous */
