/*
 * TreeNode.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_TREENODE_H_
#define BTREE_TREENODE_H_

#include "btree/AbstractTreeNode.h"
#include "base/ArrayList.h"

#include <inttypes.h>

namespace alinous {

class AbstractBtreeKey;

class TreeNode: public AbstractTreeNode {
public:
	explicit TreeNode(int numChildren, AbstractBtreeKey* key);
	explicit TreeNode(bool isroot, int numChildren, AbstractBtreeKey* key);
	virtual ~TreeNode();

	virtual bool isLeaf() const noexcept { return false; }

	bool isRoot() const noexcept;

	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);

private:
	bool root;
	ArrayList<AbstractTreeNode>* children;
};

} /* namespace alinous */

#endif /* BTREE_TREENODE_H_ */
