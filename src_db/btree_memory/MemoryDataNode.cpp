/*
 * MemoryDataNode.cpp
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#include "btree_memory/MemoryDataNode.h"

namespace alinous {

MemoryDataNode::MemoryDataNode(AbstractBtreeKey* key) : AbstractMemoryTreeNode(key) {
	this->data = nullptr;
}

MemoryDataNode::~MemoryDataNode() {
	delete this->data;
}

void MemoryDataNode::setData(IBlockObject* data) {
	delete this->data;
	this->data = data;
}

} /* namespace alinous */
