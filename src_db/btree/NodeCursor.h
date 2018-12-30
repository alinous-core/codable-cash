/*
 * NodeCursor.h
 *
 *  Created on: 2018/12/26
 *      Author: iizuka
 */

#ifndef BTREE_NODECURSOR_H_
#define BTREE_NODECURSOR_H_

#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

#include <inttypes.h>

namespace alinous {

class NodeHandle;
class BtreeStorage;
class AbstractBtreeKey;
class IBlockObject;
class AbstractTreeNode;
class AbstractBtreeKey;
class NodePosition;
class TreeNode;

class NodeCursor {
public:
	NodeCursor(const NodeCursor& inst) = delete;
	NodeCursor(NodeHandle* rootNode, BtreeStorage* store, int nodeNumber);
	virtual ~NodeCursor();

	NodePosition* pop() noexcept;
	void push(NodePosition* node) noexcept;
	NodePosition* top() noexcept;

	void insert(const AbstractBtreeKey* key, const IBlockObject* data);
	IBlockObject* gotoFirst();

	static void checkIsDataNode(NodeHandle* nodeHandle, const char* srcfile, int srcline);
private:
	void splitLeafNode(const AbstractBtreeKey* key, const IBlockObject* data);
	AbstractBtreeKey* setupTwoLists(ArrayList<NodeHandle>* list, AbstractTreeNode* node,
			RawArrayPrimitive<uint64_t>* list1, RawArrayPrimitive<uint64_t>* list2);
	void createNewRoot(TreeNode* newNode);
	void addToParent(TreeNode* newNode);
	void splitTreeNode(TreeNode* newNode);



private:
	ArrayList<NodePosition>* nodestack;
	int nodeNumber; // max inner nodes number in a node
	BtreeStorage* store;

};

} /* namespace alinous */

#endif /* BTREE_NODECURSOR_H_ */
