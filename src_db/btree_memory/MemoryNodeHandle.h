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
	void setRoot(bool isroot) noexcept;

	MemoryNodeHandle* getNextChild(const AbstractBtreeKey* key);

	MemoryNodeHandle* gotoEqMoreThanKey(const AbstractBtreeKey* key);
	MemoryNodeHandle* gotoEqKey(const AbstractBtreeKey* key);
	bool hasNext() const noexcept;
	AbstractMemoryTreeNode* nextNode() noexcept;

	AbstractMemoryTreeNode* hasKey(const AbstractBtreeKey* key) const noexcept;
	const AbstractBtreeKey* getKey() const noexcept;

	bool isFull(int nodeNumber) const noexcept;
	void addNode(AbstractMemoryTreeNode* anode) noexcept;
	void updateInnerNodes(const ArrayList<AbstractMemoryTreeNode>* list) noexcept;

	ArrayList<AbstractMemoryTreeNode>* getInnerNodes() const noexcept;

	AbstractMemoryTreeNode* getNode() const noexcept {
		return this->node;
	}

	void incPos() noexcept{
		this->pos++;
	}

private:
	AbstractMemoryTreeNode* node;
	int pos;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYNODEHANDLE_H_ */
