/*
 * MemoryTreeNode.h
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYTREENODE_H_
#define BTREE_MEMORY_MEMORYTREENODE_H_

#include "btree_memory/AbstractMemoryTreeNode.h"

#include "base/ArrayList.h"


namespace alinous {

class AbstractBtreeKey;

class MemoryTreeNode : public AbstractMemoryTreeNode {
public:
	MemoryTreeNode(int numChildren, AbstractBtreeKey* key, bool leaf);
	MemoryTreeNode(bool isroot, int numChildren, AbstractBtreeKey* key, bool leaf);
	virtual ~MemoryTreeNode();

	virtual bool isData() const noexcept;
	bool isLeaf() const noexcept;

	ArrayList<AbstractMemoryTreeNode>* getChildren() const noexcept {
		return children;
	}

private:
	bool root;
	bool leaf;
	ArrayList<AbstractMemoryTreeNode>* children;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYTREENODE_H_ */
