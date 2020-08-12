/*
 * MemoryDataNode.cpp
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#include "btree_memory/MemoryDataNode.h"

namespace alinous {

MemoryDataNode::MemoryDataNode(AbstractBtreeKey* key) : AbstractMemoryTreeNode(key) {

}

MemoryDataNode::~MemoryDataNode() {

}

} /* namespace alinous */
