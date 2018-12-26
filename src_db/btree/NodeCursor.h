/*
 * NodeCursor.h
 *
 *  Created on: 2018/12/26
 *      Author: iizuka
 */

#ifndef BTREE_NODECURSOR_H_
#define BTREE_NODECURSOR_H_

#include "base/ArrayList.h"

namespace alinous {

class NodeHandle;
class BtreeStorage;
class AbstractBtreeKey;
class IBlockObject;
class AbstractTreeNode;

class NodePosition {
public:
	explicit NodePosition(NodeHandle* nodeHandle);
	~NodePosition();

	bool isLeaf() const;

	void loadInnerNodes(BtreeStorage* store);
private:
	int pos;
	NodeHandle* node;
	ArrayList<NodeHandle>* innerNodes;
	int innerCount;
};

/****************************************************************************************/

class NodeCursor {
public:
	NodeCursor(NodeHandle* rootNode, BtreeStorage* store, int nodeNumber);
	virtual ~NodeCursor();


	NodePosition* pop() noexcept;
	void push(NodePosition* node) noexcept;
	NodePosition* top() noexcept;

	void insert(AbstractBtreeKey* key, IBlockObject* data);
private:
	ArrayList<NodePosition>* nodestack;
	int nodeNumber; // max inner nodes number in a node

};

} /* namespace alinous */

#endif /* BTREE_NODECURSOR_H_ */
