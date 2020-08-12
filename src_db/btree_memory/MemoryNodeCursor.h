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

class MemoryNodeHandle;
class AbstractBtreeKey;
class IBlockObject;

class MemoryNodeCursor {
public:
	MemoryNodeCursor(const MemoryNodeCursor& inst) = delete;
	MemoryNodeCursor(MemoryNodeHandle* rootNode, int nodeNumber);
	virtual ~MemoryNodeCursor();

	void insert(const AbstractBtreeKey* key, const IBlockObject* data);

	MemoryNodeHandle* pop() noexcept;
	void push(MemoryNodeHandle* node) noexcept;
	MemoryNodeHandle* top() noexcept;

private:
	ArrayList<MemoryNodeHandle>* nodestack;
	int nodeNumber; // max inner nodes number in a node
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYNODECURSOR_H_ */
