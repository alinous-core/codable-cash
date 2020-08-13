/*
 * MemoryNodeHandle.h
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYNODEHANDLE_H_
#define BTREE_MEMORY_MEMORYNODEHANDLE_H_

#include "base/ArrayList.h"

namespace alinous {

class AbstractMemoryTreeNode;
class AbstractBtreeKey;
class MemoryDataNode;

class MemoryNodeHandle {
public:
	explicit MemoryNodeHandle(AbstractMemoryTreeNode* node);
	virtual ~MemoryNodeHandle();

	bool isLeaf() const noexcept;
	bool isRoot() const noexcept;

	MemoryNodeHandle* getNextChild(const AbstractBtreeKey* key);
	AbstractMemoryTreeNode* hasKey(const AbstractBtreeKey* key) const noexcept;
	bool isFull(int nodeNumber) const noexcept;
	void addNode(AbstractMemoryTreeNode* anode) noexcept;

	ArrayList<AbstractMemoryTreeNode>* getInnerNodes() const noexcept;
private:
	AbstractMemoryTreeNode* node;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYNODEHANDLE_H_ */
