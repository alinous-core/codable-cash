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
class MemoryDataNode;

class MemoryTreeNode : public AbstractMemoryTreeNode {
public:
	MemoryTreeNode(int numChildren, AbstractBtreeKey* key, bool leaf);
	MemoryTreeNode(bool isroot, int numChildren, AbstractBtreeKey* key, bool leaf);
	virtual ~MemoryTreeNode();

	virtual bool isData() const noexcept;
	bool isLeaf() const noexcept;
	bool isRoot() const noexcept {return this->root;};
	void setRoot(bool root) noexcept {this->root = root;};

	ArrayList<AbstractMemoryTreeNode>* getChildren() const noexcept {
		return children;
	}
	bool isFull(int nodeNumber) const noexcept;
	void addNode(AbstractMemoryTreeNode* dnode) noexcept;
	void updateInnerNodes(const ArrayList<AbstractMemoryTreeNode>* list) noexcept;

private:
	void internalAddNode(int index, AbstractMemoryTreeNode* node) noexcept;

private:
	bool root;
	bool leaf;
	ArrayList<AbstractMemoryTreeNode>* children;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYTREENODE_H_ */
