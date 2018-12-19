/*
 * TreeNode.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_TREENODE_H_
#define BTREE_TREENODE_H_

#include "btree/AbstractTreeNode.h"

namespace alinous {

class TreeNode: public AbstractTreeNode {
public:
	TreeNode();
	virtual ~TreeNode();

	virtual bool isLeaf() const { return false; }
};

} /* namespace alinous */

#endif /* BTREE_TREENODE_H_ */
