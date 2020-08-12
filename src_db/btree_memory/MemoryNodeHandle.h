/*
 * MemoryNodeHandle.h
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYNODEHANDLE_H_
#define BTREE_MEMORY_MEMORYNODEHANDLE_H_

namespace alinous {

class AbstractTreeNode;

class MemoryNodeHandle {
public:
	explicit MemoryNodeHandle(AbstractTreeNode* node);
	virtual ~MemoryNodeHandle();

	bool isLeaf() const noexcept;
private:
	AbstractTreeNode* node;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYNODEHANDLE_H_ */
