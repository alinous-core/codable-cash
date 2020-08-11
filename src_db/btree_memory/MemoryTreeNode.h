/*
 * MemoryTreeNode.h
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYTREENODE_H_
#define BTREE_MEMORY_MEMORYTREENODE_H_

#include "btree/AbstractTreeNode.h"

#include "base/ArrayList.h"

namespace alinous {

class AbstractBtreeKey;

class MemoryTreeNode : public AbstractTreeNode {
public:
	MemoryTreeNode(int numChildren, AbstractBtreeKey* key, bool reaf);
	MemoryTreeNode(bool isroot, int numChildren, AbstractBtreeKey* key, bool reaf);
	virtual ~MemoryTreeNode();

	virtual bool isData() const noexcept;
private:
	bool root;
	bool leaf;
	ArrayList<AbstractTreeNode>* children;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYTREENODE_H_ */
