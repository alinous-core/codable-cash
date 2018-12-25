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
#include "base/RawArrayPrimitive.h"

#include <inttypes.h>

namespace alinous {

class AbstractBtreeKey;
class BTreeKeyFactory;

class TreeNode: public AbstractTreeNode {
private:
	TreeNode();
public:
	explicit TreeNode(int numChildren, AbstractBtreeKey* key, bool reaf);
	explicit TreeNode(bool isroot, int numChildren, AbstractBtreeKey* key, bool reaf);
	virtual ~TreeNode();

	virtual bool isData() const noexcept { return false; }

	bool isRoot() const noexcept;
	bool isLeaf() const noexcept;

	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);
	static TreeNode* fromBinary(ByteBuffer* in, BTreeKeyFactory* factory);

private:
	bool root;
	bool leaf;
	RawArrayPrimitive<uint64_t>* children;
};

} /* namespace alinous */

#endif /* BTREE_TREENODE_H_ */
