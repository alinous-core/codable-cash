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

class MemoryNodeCursor {
public:
	MemoryNodeCursor(const MemoryNodeCursor& inst) = delete;
	MemoryNodeCursor(MemoryNodeHandle* rootNode, int nodeNumber);
	virtual ~MemoryNodeCursor();

	void insert(const AbstractBtreeKey* key, IBlockObject* data);

	MemoryNodeHandle* pop() noexcept;
	void push(MemoryNodeHandle* node) noexcept;
	MemoryNodeHandle* top() noexcept;

private:
	void splitLeafNode(const AbstractBtreeKey* key, IBlockObject* data);
	AbstractBtreeKey* setupTwoLists(ArrayList<AbstractMemoryTreeNode>* list, AbstractMemoryTreeNode* node,
			ArrayList<AbstractMemoryTreeNode>* list1, ArrayList<AbstractMemoryTreeNode>* list2);

private:
	ArrayList<MemoryNodeHandle>* nodestack;
	int nodeNumber; // max inner nodes number in a node
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYNODECURSOR_H_ */
