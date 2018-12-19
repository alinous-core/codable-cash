/*
 * AbstractTreeNode.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_ABSTRACTTREENODE_H_
#define BTREE_ABSTRACTTREENODE_H_

namespace alinous {

class AbstractTreeNode {
public:
	AbstractTreeNode();
	virtual ~AbstractTreeNode();

	virtual bool isLeaf() const = 0;
};

} /* namespace alinous */

#endif /* BTREE_ABSTRACTTREENODE_H_ */
