/*
 * MemoryNodeHandle.h
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYNODEHANDLE_H_
#define BTREE_MEMORY_MEMORYNODEHANDLE_H_

namespace alinous {

class AbstractMemoryTreeNode;
class AbstractBtreeKey;
class MemoryDataNode;

class MemoryNodeHandle {
public:
	explicit MemoryNodeHandle(AbstractMemoryTreeNode* node);
	virtual ~MemoryNodeHandle();

	bool isLeaf() const noexcept;

	MemoryNodeHandle* getNextChild(const AbstractBtreeKey* key);
	AbstractMemoryTreeNode* hasKey(const AbstractBtreeKey* key) const noexcept;
	bool isFull(int nodeNumber) const noexcept;
	void addNode(AbstractMemoryTreeNode* anode) noexcept;
private:
	AbstractMemoryTreeNode* node;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYNODEHANDLE_H_ */
