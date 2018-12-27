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
class AbstractBtreeKey;

class NodePosition {
public:
	explicit NodePosition(NodeHandle* nodeHandle);
	~NodePosition();

	bool isLeaf() const;
	bool hasKey(const AbstractBtreeKey* key) const;
	bool isFull(int nodeNumber) const noexcept;

	void loadInnerNodes(BtreeStorage* store);

	static void checkNoNull(NodeHandle* nodeHandle, const char* srcfile, int srcline) noexcept(false);
private:
	int pos;
	NodeHandle* node;
	ArrayList<NodeHandle>* innerNodes;
	int innerCount;
};

/****************************************************************************************/

class NodeCursor {
public:
	NodeCursor(const NodeCursor& inst) = delete;
	NodeCursor(NodeHandle* rootNode, BtreeStorage* store, int nodeNumber);
	virtual ~NodeCursor();


	NodePosition* pop() noexcept;
	void push(NodePosition* node) noexcept;
	NodePosition* top() noexcept;

	void insert(const AbstractBtreeKey* key, const IBlockObject* data);
private:
	void splitNode();

private:
	ArrayList<NodePosition>* nodestack;
	int nodeNumber; // max inner nodes number in a node
	BtreeStorage* store;

};

} /* namespace alinous */

#endif /* BTREE_NODECURSOR_H_ */
