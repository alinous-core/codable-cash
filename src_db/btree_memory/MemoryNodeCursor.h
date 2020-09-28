/*
 * MemoryNodeCursor.h
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYNODECURSOR_H_
#define BTREE_MEMORY_MEMORYNODECURSOR_H_

#include "base/ArrayList.h"

namespace alinous {

class AbstractMemoryTreeNode;
class MemoryNodeHandle;
class AbstractBtreeKey;
class IBlockObject;
class MemoryTreeNode;
class BtreeOnMemory;

class MemoryNodeCursor {
public:
	MemoryNodeCursor(const MemoryNodeCursor& inst) = delete;
	MemoryNodeCursor(MemoryNodeHandle* rootNode, int nodeNumber, BtreeOnMemory* btree);
	virtual ~MemoryNodeCursor();

	void insert(const AbstractBtreeKey* key, IBlockObject* data);

	IBlockObject* find(const AbstractBtreeKey* key);

	IBlockObject* gotoFirst() noexcept;
	IBlockObject* gotoKey(const AbstractBtreeKey* key) noexcept;
	IBlockObject* getNext() noexcept;
	const AbstractBtreeKey* getCurrentKey();

	void pop() noexcept;
	void push(MemoryNodeHandle* node) noexcept;
	MemoryNodeHandle* top() noexcept;

private:
	void splitLeafNode(const AbstractBtreeKey* key, IBlockObject* data);
	AbstractBtreeKey* setupTwoLists(ArrayList<AbstractMemoryTreeNode>* list, AbstractMemoryTreeNode* node,
			ArrayList<AbstractMemoryTreeNode>* list1, ArrayList<AbstractMemoryTreeNode>* list2);
	void createNewRoot(MemoryTreeNode* newNode);
	void addToParent(MemoryTreeNode* newNode);
	void splitTreeNode(MemoryTreeNode* node);
	MemoryNodeHandle* gotoLeaf(const AbstractBtreeKey* key);

private:
	ArrayList<MemoryNodeHandle>* nodestack;
	int nodeNumber; // max inner nodes number in a node

	BtreeOnMemory* btree;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYNODECURSOR_H_ */
