/*
 * MemoryDataNode.h
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYDATANODE_H_
#define BTREE_MEMORY_MEMORYDATANODE_H_

#include "btree_memory/AbstractMemoryTreeNode.h"

namespace alinous {

class AbstractBtreeKey;

class MemoryDataNode : public AbstractMemoryTreeNode {
public:
	MemoryDataNode(AbstractBtreeKey* key);
	virtual ~MemoryDataNode();
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYDATANODE_H_ */
